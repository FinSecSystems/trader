#pragma once

#include "appsubsystem.h"
#include "genericdatabase.h"
#include "interface.h"
#include "interfacehelper.h"
#include "tinyfsm.hpp"

namespace trader
{

    class MarketDataSubSystem;

    class MarketDataEventProcessor : public BufferedConnection< Interface::MessageReceivingConnection >
    {
      public:
        MarketDataEventProcessor(MarketDataSubSystem *_sys)
            : sys(_sys)
            , BufferedConnection(10)
        {
        }

        void SecurityList(Poco::AutoPtr< SecurityListData > securityListData) override;
        void MarketDataSnapshotFullRefresh(
            Poco::AutoPtr< MarketDataSnapshotFullRefreshData > marketDataSnapshotFullRefreshData) override;
        void MarketDataIncrementalRefresh(
            Poco::AutoPtr< MarketDataIncrementalRefreshData > marketDataIncrementalRefresh) override;

        MarketDataSubSystem *sys;
    };

#define InterfaceEvent(x)                                                                                              \
    struct On##x : public MarketDataEvent                                                                              \
    {                                                                                                                  \
        On##x(MarketDataSubSystem *_sys, Poco::AutoPtr< Interface::x##Data > param)                                    \
            : MarketDataEvent(_sys)                                                                                    \
            , message(param)                                                                                           \
        {                                                                                                              \
        }                                                                                                              \
        Poco::AutoPtr< Interface::x##Data > message;                                                                   \
    };                                                                                                                 \
    virtual void react(On##x const &) {}

    class MarketDataStateChart : public tinyfsm::Fsm< MarketDataStateChart >
    {
      public:
        typedef tinyfsm::FsmList< MarketDataStateChart > MarketDataFSMList;

        template < typename E > void send_event(E const &event) { MarketDataFSMList::template dispatch< E >(event); }

        // Events
        struct MarketDataEvent : tinyfsm::Event
        {
            MarketDataEvent(MarketDataSubSystem *_sys)
                : sys(_sys)
            {
            }
            MarketDataSubSystem *sys;
        };

        struct Start : public MarketDataEvent
        {
            Start(MarketDataSubSystem *_sys)
                : MarketDataEvent(_sys)
            {
            }
        };

        InterfaceEvent(SecurityList);
        InterfaceEvent(MarketDataSnapshotFullRefresh);
        InterfaceEvent(MarketDataIncrementalRefresh);

        void react(tinyfsm::Event const &){};
        virtual void react(Start const &) {}
        virtual void entry(void){};
        virtual void exit(void){};
    };

    class MarketDataSubSystem : public AppSubsystem, public Poco::Runnable
    {
      public:
        MarketDataSubSystem()
            : app(nullptr)
        {
            eventProcessor = new MarketDataEventProcessor(this);
        }

        const char *name() const override { return "MarketData"; }

        void initialize(Application &application) override;

        void uninitialize() override;

        void run() override;

        // typedef std::map<Poco::Int32, Interface::SecListGrpObject::NoRelatedSym> SymMap;

        struct MarketData
        {
            MarketData()
                : lastCachedId(0)
            {
            }
            Poco::AutoPtr< GenericDatabase::Trade_History > storage;
            // SymMap cache;
            Poco::Int32 lastCachedId;
        };

        TraderApp *app;
        MarketDataStateChart stateChart;

        typedef std::unordered_map< std::string, MarketData > SymIDMap;
        // SymIDMap marketToTradeHistoryMap;

        typedef std::unordered_map< std::string, SymIDMap > ConnectionMarketMap;
        ConnectionMarketMap connectionMarketMap;

        bool useStorage; // Use physical storage

        void retrieveMarkets(std::vector< std::string > &_markets);

        void requestMarketData(const std::string &_for_market);
    };

} // namespace trader
