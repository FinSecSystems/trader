#pragma once

#include "db.h"
#include "app.h"
#include "interface.h"

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

        Poco::AutoPtr<Db> dB;
        ThreadPool pool;
        std::vector<AutoPtr<trader::Interface::Connection>> connections;
        AutoPtr<trader::Interface::Connection> appConnection;

	protected:
		void defineOptions(Poco::Util::OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void displayHelp();
        Poco::Util::AbstractConfiguration& appConfig();
		int main(const std::vector<std::string>& args) override;

	};
}
