#pragma once
#pragma once

#include "app.h"
#include "applicationhelper.h"
#include "connectionhelper.h"
#include "db.h"
#include "interface.h"
#include "tinyfsm.hpp"

namespace trader
{

    class AppSubsystem : public Poco::Util::Subsystem
    {
      public:
        Poco::AutoPtr< Interface::Connection > eventProcessor;

        void ProcessMessage(Poco::AutoPtr< Interface::IMessageData > _messageData)
        {
            eventProcessor->ProcessMessage(_messageData);
        }
    };

} // namespace trader
