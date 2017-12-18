#include "stdafx.h"
#include "dataconnector/db.h"
#include "dataconnector/app.h"
#include "dataconnector/connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "appconnection.h"
#include "Poco/FIFOEvent.h"
#include "Poco/KeyValueArgs.h"

namespace trader {


    AppConnection::AppConnection()
    {

    }

    AppConnection::~AppConnection()
    {

    }

    void AppConnection::ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData)
    {
        Poco::FIFOEvent<const Poco::AutoPtr< Interface::IMessageData >, Poco::FastMutex > evt;
        MessageMap::iterator it;
        it = messageMap.find(_messageData->messageId);
        if (it != messageMap.end())
        {
            (it->second)(_messageData);
        }
    }

    void AppConnection::RegisterCallback(Poco::AutoPtr<Interface::IMessageData> _messageData, AppConnectionCallback callback)
    {
        MessageMap::iterator it;
        it = messageMap.find(_messageData->messageId);
        if (it != messageMap.end())
        {
            //it->second += (_messageData);
        }
    }

    void AppConnection::UnregisterCallback(Poco::AutoPtr<Interface::IMessageData> _messageData, AppConnectionCallback callback)
    {

    }

}
