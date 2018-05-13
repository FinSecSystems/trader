#pragma once

#include "applicationhelper.h"
#include "interface.h"

namespace trader
{

    class AppConnection : public Interface::CallConnection
    {
      public:
        AppConnection(ApplicationHelper *_app);

        ~AppConnection();

        void ProcessMessage(Poco::AutoPtr< Interface::IMessageData > _messageData) override;

      private:
        ApplicationHelper *app;
    };
} // namespace trader
