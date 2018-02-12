#pragma once

namespace trader {

	class AppConnection : public Interface::Connection
	{
	public:

        AppConnection(TraderApp* _app);

        ~AppConnection();

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData) override;

        void SecurityList(Poco::AutoPtr<SecurityListData> securityListData) override;

    private:
        TraderApp* app;
	};
}
