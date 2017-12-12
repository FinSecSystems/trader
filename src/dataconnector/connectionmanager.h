#pragma once
#include "interface.h"

namespace trader {

    class ConnectionManager : public SingletonHolder<ConnectionManager>
    {
    public:
        ConnectionManager();

        ~ConnectionManager();

        Poco::AutoPtr<Interface::Connection> getConnection(const std::string& connectionString);

    };

};