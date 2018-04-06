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
            stateChart.send_event(MarketDataStateChart::Start(this));
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

    void MarketDataSubSystem::retrieveMarkets(std::vector<string>& _markets)
    {
        for (auto& connection : connectionMarketMap)
        {
            string connectionName = connection.first;
            for (auto& market : connection.second)
            {
                ostringstream marketNameStream;
                marketNameStream << connectionName << ";";
                marketNameStream << market.first;
                _markets.push_back(marketNameStream.str());
            }
        }
    }

    void MarketDataSubSystem::requestMarketData(const string& _for_market)
    {
        static atomic<int32_t> marketDataRequestDataIdx;
        StringTokenizer marketTokenString(_for_market, ";,:", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
        poco_assert(marketTokenString.count() == 2);

        string& connectionName = marketTokenString[0];
        string& securityName = marketTokenString[1];

        bool topOfBook = 1;
        ConnectionMarketMap::iterator it = connectionMarketMap.find(connectionName);
        if (it == connectionMarketMap.end())
        {
            topOfBook = 0;
        }

        AutoPtr<Connection> connection = app->getConnection(connectionName);

        AutoPtr<MarketDataRequestData> marketDataRequestData = new MarketDataRequestData();
        ostringstream str;
        str << "MDR" << app->name() << ++marketDataRequestDataIdx << endl;
        marketDataRequestData->mDReqID = str.str();
        marketDataRequestData->subscriptionRequestType = Interface::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES;
        marketDataRequestData->marketDepth = topOfBook;
        marketDataRequestData->instrmtMDReqGrp.noRelatedSym.emplace_back();
        auto& noRelatedSym = marketDataRequestData->instrmtMDReqGrp.noRelatedSym.back();
        noRelatedSym.instrument.symbol = securityName;
        connection->MarketDataRequest(marketDataRequestData);       
    }

    void MarketDataEventProcessor::SecurityList(AutoPtr<SecurityListData> securityListData)
    {
        sys->stateChart.send_event(MarketDataStateChart::OnSecurityList(sys, securityListData));
    }

    void MarketDataEventProcessor::MarketDataSnapshotFullRefresh(AutoPtr<MarketDataSnapshotFullRefreshData> marketDataSnapshotFullRefreshData)
    {
        sys->stateChart.send_event(MarketDataStateChart::OnMarketDataSnapshotFullRefresh(sys, marketDataSnapshotFullRefreshData));
    }

    void MarketDataEventProcessor::MarketDataIncrementalRefresh(AutoPtr<MarketDataIncrementalRefreshData> marketDataIncrementalRefreshData)
    {
        sys->stateChart.send_event(MarketDataStateChart::OnMarketDataIncrementalRefresh(sys, marketDataIncrementalRefreshData));
    }

    class ProcessSecurityList;

    class Init : public MarketDataStateChart
    {

        void react(Start const & e) override
        {
            std::vector<AutoPtr<trader::Interface::Connection>> connections;
            e.sys->app->getConnections(connections);
            for (auto& connection : connections)
            {
                AutoPtr<SecurityListRequestData> securityListRequestData = new SecurityListRequestData();
                ostringstream str;
                str << "SLR" << e.sys->app->name() << ++securityListRequestDataIdx << endl;
                securityListRequestData->securityReqID = str.str();
                connection->SecurityListRequest(securityListRequestData);
            }
            transit<ProcessSecurityList>();
        };

        static atomic<int32_t> securityListRequestDataIdx;
    };

    class ListenState;

    class ProcessSecurityList : public MarketDataStateChart
    {

        void react(OnSecurityList const & e) override
        {
            SecurityListData const& securityListData = *(e.message);

            MarketDataSubSystem::ConnectionMarketMap::iterator itConnection = e.sys->connectionMarketMap.find(securityListData.getSourceConnection());
            
            MarketDataSubSystem::SymIDMap *marketToTradeHistoryMapPtr = nullptr;
            if (itConnection == e.sys->connectionMarketMap.end())
            {
                pair<MarketDataSubSystem::ConnectionMarketMap::iterator, bool> ret = e.sys->connectionMarketMap.insert({ securityListData.getSourceConnection(), MarketDataSubSystem::SymIDMap() });
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
                cout << syms.instrument.symbol << endl;
            }
            
            AutoPtr<Db> db = DbManager::instance.getDb();
            for (auto& syms : securityListData.secListGrp.noRelatedSym)
            {
                //Add market if it does not already exist
                MarketDataSubSystem::SymIDMap::const_iterator marketExists = marketToTradeHistoryMap.find(syms.instrument.symbol);
                if (marketExists == marketToTradeHistoryMap.end())
                {
                    AutoPtr<GenericDatabase::Trade_History> tradeHistoryTable = new GenericDatabase::Trade_History(db->getDbSession(), syms.instrument.symbol);
                    MarketDataSubSystem::MarketData marketData;
                    marketData.storage = tradeHistoryTable;
                    marketToTradeHistoryMap.insert({ syms.instrument.symbol, marketData });
                    if (e.sys->useStorage)
                    {
                        tradeHistoryTable->init();
                    }
                }
            }

            e.sys->app->stateChart.send_event(AppStateChart::OnMarketDataReady());

            //TODO: Check if a market has been removed and send an event

            transit<ListenState>();
        };

    };

    class ListenState : public MarketDataStateChart
    {
        void react(OnMarketDataSnapshotFullRefresh const & e) override
        {
        }

        void react(OnMarketDataIncrementalRefresh const & e) override
        {
        }

    };

    atomic<int32_t> Init::securityListRequestDataIdx;

}

FSM_INITIAL_STATE(trader::MarketDataStateChart, trader::Init);
