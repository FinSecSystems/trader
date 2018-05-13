#pragma once

#include "app.h"
#include "applicationhelper.h"
#include "appsubsystem.h"
#include "connectionhelper.h"
#include "db.h"
#include "interface.h"
#include "tinyfsm.hpp"
#pragma once

namespace trader
{
    class BittrexApp : public ApplicationHelper
    {

      protected:
        int main(const std::vector< std::string > &args) override;
    };
} // namespace trader
