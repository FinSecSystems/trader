#include "stdafx.h"

#include "appconnection.h"
#include "app.h"
#include "appsubsystem.h"
#include "connectionmanager.h"
#include "interface.h"

namespace trader
{

    AppConnection::AppConnection(ApplicationHelper *_app)
        : app(_app)
    {
    }

    AppConnection::~AppConnection() {}

    void AppConnection::ProcessMessage(Poco::AutoPtr< Interface::IMessageData > _messageData)
    {
        Poco::UInt32 skip = 1; // 1st entry in the list is the application
        for (auto &subSystem : app->subsystems())
        {
            if (!skip--)
            {
                subSystem.unsafeCast< AppSubsystem >()->ProcessMessage(_messageData);
            }
        }
    }

} // namespace trader
