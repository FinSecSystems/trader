#pragma once

#include "app.h"
#include "applicationhelper.h"
#include "appsubsystem.h"
#include "connectionhelper.h"
#include "db.h"
#include "interface.h"
#pragma once

namespace trader
{
    class SampleApp : public ApplicationHelper
    {

      protected:
        int main(const std::vector< std::string > &args) override;
    };
} // namespace trader
