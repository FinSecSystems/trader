#include "stdafx.h"
#include "connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "marketdatasubsystem.h"
#include "genericdatabase.h"
#include "db.h"

namespace trader {

    void MarketDataSubSystem::initialize(Application& application)
    {
        app = static_cast<TraderApp*>(&application);
        AutoPtr<AbstractConfiguration> properties(app->appConfig().createView("MarketDataSubSystem"));
        if (properties->hasProperty("usestorage"))
        {
            useStorage = properties->getBool("usestorage");
        }

        try
        {
            MarketDataStateChart::MarketDataFSMList::start();
            stateChart.send_event(MarketDataStateChart::Start());
            app->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
        }
        catch (...)
        {
            throw;
        }
    }

    void MarketDataSubSystem::uninitialize()
    {

    }

    void MarketDataSubSystem::run()
    {
        eventProcessor.unsafeCast<MarketDataEventProcessor>()->Run();
        app->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
    }

    void MarketDataSubSystem::getMarkets(std::vector<std::string>& _markets)
    {
        for (auto& connection : connectionMarketMap)
        {
            std::string connectionName = connection.first;
            for (auto& market : connection.second)
            {
                std::ostringstream marketNameStream;
                marketNameStream << connectionName << ";";
                marketNameStream << market.first;
                _markets.push_back(marketNameStream.str());
            }
        }
    }

    void MarketDataEventProcessor::SecurityList(Poco::AutoPtr<SecurityListData> securityListData)
    {
        marketDataSubSystem->stateChart.send_event(MarketDataStateChart::OnReceiveSecurityList(securityListData));
    }

    class ProcessSecurityList;

    class Init : public MarketDataStateChart
    {
        void entry() override
        {

        }

        void react(Start const & e) override
        {
            (void)e;
            for (auto& connection : MarketDataSubSystem::instance->app->connections)
            {
                Poco::AutoPtr<Interface::Connection::SecurityListRequestData> securityListRequestData = new Interface::Connection::SecurityListRequestData();
                ostringstream str;
                str << "SLR" << MarketDataSubSystem::instance->app->name() << ++securityListRequestDataIdx << endl;
                securityListRequestData->securityReqID = str.str();
                connection->SecurityListRequest(securityListRequestData);
            }
            transit<ProcessSecurityList>();
        };

        static std::atomic<std::int32_t> securityListRequestDataIdx;
    };

    class ProcessSecurityList : public MarketDataStateChart
    {
        void entry() override
        {

        }

        void react(OnReceiveSecurityList const & e) override
        {
            Interface::Connection::SecurityListData const& securityListData = *(e.securityList);
            MarketDataSubSystem* sys = MarketDataSubSystem::instance;

            MarketDataSubSystem::ConnectionMarketMap::iterator itConnection = sys->connectionMarketMap.find(securityListData.getSourceConnection());
            
            MarketDataSubSystem::SymIDMap *marketToTradeHistoryMapPtr = nullptr;
            if (itConnection == sys->connectionMarketMap.end())
            {
                std::pair<MarketDataSubSystem::ConnectionMarketMap::iterator, bool> ret = sys->connectionMarketMap.insert({ securityListData.getSourceConnection(), MarketDataSubSystem::SymIDMap() });
                poco_assert(ret.second);
                marketToTradeHistoryMapPtr = &(ret.first->second);
                Logger::get("Logs").information("MarketDataSubSystem: Received Security List from %s", securityListData.getSourceConnection());
            }
            else
            {
                marketToTradeHistoryMapPtr = &(itConnection->second);
            }
            MarketDataSubSystem::SymIDMap& marketToTradeHistoryMap = *marketToTradeHistoryMapPtr;

            for (auto& syms : securityListData.secListGrp.noRelatedSym)
            {
                std::cout << syms.instrument.symbol << std::endl;
            }
            
            AutoPtr<Db> db = DbManager::instance.getDb();
            for (auto& syms : securityListData.secListGrp.noRelatedSym)
            {
                //Add market if it does not already exist
                MarketDataSubSystem::SymIDMap::const_iterator marketExists = marketToTradeHistoryMap.find(syms.instrument.symbol);
                if (marketExists == marketToTradeHistoryMap.end())
                {
                    Poco::AutoPtr<GenericDatabase::Trade_History> tradeHistoryTable = new GenericDatabase::Trade_History(db->getDbSession(), syms.instrument.symbol);
                    MarketDataSubSystem::MarketData marketData;
                    marketData.storage = tradeHistoryTable;
                    marketToTradeHistoryMap.insert({ syms.instrument.symbol, marketData });
                    if (MarketDataSubSystem::instance->useStorage)
                    {
                        tradeHistoryTable->init();
                    }
                }
            }

            sys->app->stateChart.send_event(AppStateChart::OnMarketDataReady());

            //TODO: Check if a market has been removed and send an event

            transit<Init>();
        };

    };

    std::atomic<std::int32_t> Init::securityListRequestDataIdx;

    MarketDataSubSystem* MarketDataSubSystem::instance;
}

FSM_INITIAL_STATE(trader::MarketDataStateChart, trader::Init);
