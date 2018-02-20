#pragma once

namespace trader {

	class AppConnection : public Interface::CallConnection
	{
	public:

        AppConnection(TraderApp* _app);

        ~AppConnection();

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData) override;

    private:
        TraderApp* app;
	};
}
