#pragma once

#include "db.h"
#include "app.h"
#include "interface.h"
#include "tinyfsm.hpp"
#include "connectionhelper.h"
#include "applicationhelper.h"
#include "appsubsystem.h"

namespace trader {

    class TraderApp;

    class AppStateChart : public tinyfsm::Fsm<AppStateChart>
    {
    public:
        typedef tinyfsm::FsmList<AppStateChart> AppFSMList;

        template<typename E>
        void send_event(E const & event)
        {
            AppFSMList::template dispatch<E>(event);
        }

        //Events
        struct OnMarketDataReady : tinyfsm::Event {};
        struct OnMarketUpdate : tinyfsm::Event {};

        void react(tinyfsm::Event const&) {};
        virtual void react(OnMarketDataReady const&) {};
        virtual void react(OnMarketUpdate const&) {};
        virtual void entry(void) {};
        virtual void exit(void) {};

    };

    class TraderApp : public ApplicationHelper, public ConnectionHelper
	{
	public:
        AppStateChart stateChart;
	protected:
		int main(const std::vector<std::string>& args) override;
	};
}
