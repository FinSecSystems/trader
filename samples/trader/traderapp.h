#pragma once

#include "db.h"
#include "app.h"
#include "interface.h"
#include "tinyfsm.hpp"

namespace trader {

    class TraderSubsystem : public Poco::Util::Subsystem
    {
    public:
        Poco::AutoPtr<Interface::Connection> eventProcessor;

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData)
        {
            eventProcessor->ProcessMessage(_messageData);
        }
    };

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

        void react(tinyfsm::Event const&) {};
        virtual void react(OnMarketDataReady const&) {};
        virtual void entry(void) {};
        virtual void exit(void) {};

    };

    class TraderApp : public App
	{
	public:
        TraderApp()
		{
		}

		~TraderApp()
		{
		}

		bool findFile(Poco::Path& path) const override;

        Poco::Util::AbstractConfiguration& appConfig();

        ThreadPool pool;
        std::vector<AutoPtr<trader::Interface::Connection>> connections;
        AutoPtr<trader::Interface::Connection> appConnection;
        AppStateChart stateChart;

	protected:
		void defineOptions(Poco::Util::OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void displayHelp();
		int main(const std::vector<std::string>& args) override;

	};
}
