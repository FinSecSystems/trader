#pragma once

#include "db.h"
#include "app.h"
#include "interface.h"
#include "tinyfsm.hpp"
#include "applicationhelper.h"
#include "connectionhelper.h"

namespace trader {

    class AppSubsystem : public Poco::Util::Subsystem
    {
    public:
        Poco::AutoPtr<Interface::Connection> eventProcessor;

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData)
        {
            eventProcessor->ProcessMessage(_messageData);
        }
    };

}
