#pragma once

#include "tinyfsm.hpp"

namespace trader {

    class MarketDataSubSystem;

    class MarketDataEventProcessor : public Interface::Connection
    {
    public:
        MarketDataEventProcessor(MarketDataSubSystem* _sys)
            : marketDataSubSystem(_sys)
            , messageQueue(10)
        {}

        void SecurityList(Poco::AutoPtr<SecurityListData> securityListData) override;

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData) override;

        void Run();

        BasicFIFOBuffer<Interface::IMessageData*> messageQueue;
        MarketDataSubSystem* marketDataSubSystem;
    };

    class MarketDataStateChart : public tinyfsm::Fsm<MarketDataStateChart>
    {
    public:

        typedef tinyfsm::FsmList<MarketDataStateChart> MarketDataFSMList;

        template<typename E>
        void send_event(E const & event)
        {
            MarketDataFSMList::template dispatch<E>(event);
        }

        //Events
        struct PullData : tinyfsm::Event {};
        struct Start : tinyfsm::Event {};
        struct OnReceiveSecurityList : tinyfsm::Event
        {
            OnReceiveSecurityList(Poco::AutoPtr<Interface::Connection::SecurityListData> securityListData)
                : securityList(securityListData)
            {}

            Poco::AutoPtr<Interface::Connection::SecurityListData> securityList;
        };

        void react(tinyfsm::Event const&) {};
        virtual void react(Start const&) {}
        virtual void react(OnReceiveSecurityList const&) {}
        virtual void entry(void) {};
        virtual void exit(void) {};

        MarketDataSubSystem* marketDataSubSystem;
    };

	class MarketDataSubSystem : public TraderSubsystem, public Poco::Runnable
	{
	public:
        MarketDataSubSystem() :
            app(nullptr)
		{
            poco_assert(MarketDataSubSystem::instance == nullptr);
            MarketDataSubSystem::instance = this;
            eventProcessor = new MarketDataEventProcessor(this);
		}

		~MarketDataSubSystem()
		{
            MarketDataSubSystem::instance = nullptr;
		}

        const char* name() const override
        {
            return "MarketData";
        }

        void initialize(Application& application) override;

        void uninitialize() override;

        void run() override;

        TraderApp* app;
        MarketDataStateChart stateChart;

        static MarketDataSubSystem* instance;
	};

}
