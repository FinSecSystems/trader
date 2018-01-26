#pragma once

namespace trader {

    class AppConnectionCallbackInterface
    {
    public:
        void* NotifyMethod(const Poco::AutoPtr< Interface::IMessageData > messageData)
        {
            this->OnSuccess(messageData);
        }

        virtual void OnSuccess(const Poco::AutoPtr< Interface::IMessageData > messageData) = 0;
    };

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

        void RegisterCallback(Interface::MessageId messageId, const AppConnectionCallbackInterface& callback);

        void UnregisterCallback(Interface::MessageId messageId, const AppConnectionCallbackInterface& callback);

        MessageMap messageMap;

	};
}
