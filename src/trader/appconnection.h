#pragma once

namespace trader {

	class AppConnection : public Interface::Connection
	{
	public:

        typedef void(*AppConnectionCallback)(Poco::AutoPtr<Interface::IMessageData> _messageData);
        typedef Poco::FIFOEvent<const Poco::AutoPtr< Interface::IMessageData >, Poco::FastMutex > MessageEvent;
        typedef std::map<Interface::MessageId, MessageEvent> MessageMap;
        typedef std::pair<Interface::MessageId, MessageEvent> MessageIdEventKVPair;

        AppConnection();

        ~AppConnection();

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData) override;

        void RegisterCallback(Poco::AutoPtr<Interface::IMessageData> _messageData, AppConnectionCallback callback);

        void UnregisterCallback(Poco::AutoPtr<Interface::IMessageData> _messageData, AppConnectionCallback callback);

        MessageMap messageMap;

	};
}
