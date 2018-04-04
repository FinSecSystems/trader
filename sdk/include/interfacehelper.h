#pragma once

namespace trader {

    template <class ConnectionType> class BufferedConnection : public ConnectionType
    {
    public:
        BufferedConnection(std::size_t _bufferSize)
            : messageQueue(_bufferSize)
        {
        }

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData) override
        {
            _messageData->duplicate();
            Interface::IMessageData* msgData = _messageData.get();
            messageQueue.write(&msgData, 1);
        }

        virtual void Run()
        {
            std::size_t queueSize = messageQueue.used();
            if (queueSize)
            {
                Interface::IMessageData** tempQueue = new Interface::IMessageData*[queueSize];
                std::size_t itemsRead = messageQueue.read(tempQueue, queueSize);
                for (size_t i = 0; i < itemsRead; ++i)
                {
                    Interface::IMessageData* messageData = tempQueue[i];
                    Poco::AutoPtr<Interface::IMessageData> messageDataPtr = messageData;
                    ConnectionType::ProcessMessage(messageDataPtr);
                }
                delete[] tempQueue;
            }
        }

    private:
        BasicFIFOBuffer<Interface::IMessageData*> messageQueue;
    };
}
