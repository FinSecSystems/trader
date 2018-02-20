#include "stdafx.h"
#include "connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "marketdatasubsystem.h"

namespace trader {

    void MarketDataSubSystem::initialize(Application& application)
    {
        app = static_cast<TraderApp*>(&application);
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

            for (auto& syms : securityListData.secListGrp.noRelatedSym)
            {
                std::cout << syms.instrument.symbol << std::endl;
            }
            transit<Init>();
        };

    };

    std::atomic<std::int32_t> Init::securityListRequestDataIdx;

    MarketDataSubSystem* MarketDataSubSystem::instance;
}

FSM_INITIAL_STATE(trader::MarketDataStateChart, trader::Init);

