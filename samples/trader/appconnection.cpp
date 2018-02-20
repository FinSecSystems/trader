#include "stdafx.h"
#include "db.h"
#include "app.h"
#include "connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "appconnection.h"
#include "Poco/FIFOEvent.h"
#include "Poco/KeyValueArgs.h"
#include "Poco/Delegate.h"

namespace trader {


    AppConnection::AppConnection(TraderApp* _app)
        : app(_app)
    {}

    AppConnection::~AppConnection()
    {

    }

    void AppConnection::ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData)
    {
        Poco::UInt32 skip = 1; //1st entry in the list is the application
        for (auto& subSystem : app->subsystems())
        {
            if (!skip--)
            {
                subSystem.unsafeCast<TraderSubsystem>()->ProcessMessage(_messageData);
            }
        }
    }

}
