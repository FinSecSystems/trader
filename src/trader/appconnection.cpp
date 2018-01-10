#include "stdafx.h"
#include "dataconnector/db.h"
#include "dataconnector/app.h"
#include "dataconnector/connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "appconnection.h"
#include "Poco/FIFOEvent.h"
#include "Poco/KeyValueArgs.h"
#include "Poco/Delegate.h"

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

    void AppConnection::RegisterCallback(Interface::MessageId messageId, const AppConnectionCallbackInterface& callback)
    {
        MessageMap::iterator it;
        it = messageMap.find(messageId);
        if (it != messageMap.end())
        {
            MessageEvent& evt = it->second;
           // evt += Delegate<AppConnectionCallbackInterface, Interface::MessageId>(&callback, &AppConnectionCallbackInterface::NotifyMethod);
        }
        else
        {
            MessageEvent evt;
          //  evt += Delegate<AppConnectionCallbackInterface, MessageId >(&callback, &AppConnectionCallbackInterface::NotifyMethod);
          //  messageMap.insert(std::make_pair(messageId, evt));
        }
    }

    void AppConnection::UnregisterCallback(Interface::MessageId messageId, const AppConnectionCallbackInterface& callback)
    {
        MessageMap::iterator it;
        it = messageMap.find(messageId);
        if (it != messageMap.end())
        {
            MessageEvent& evt = it->second;
         //   evt -= Delegate<AppConnectionCallbackInterface, Interface::MessageId >(&callback, &AppConnectionCallbackInterface::NotifyMethod);
            if (!evt.hasDelegates())
            {
              //  messageMap.erase(it);
            }
        }
        else
        {
            poco_unexpected();
        }
    }

}
