#include "stdafx.h"
#include "connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "marketdatasubsystem.h"

namespace trader {

    void MarketDataSubSystem::initialize(Application& application)
    {
        app = static_cast<TraderApp*>(&application);
        try
        {
            app->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
        }
        catch (...)
        {
            throw;
        }
    }

    void MarketDataSubSystem::uninitialize()
    {

    }

    void MarketDataSubSystem::run()
    {
        app->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
    }

}

