#pragma once
#include "interface.h"

namespace trader {

    class ConnectionManager : public SingletonHolder<ConnectionManager>
    {
    public:
        ConnectionManager();

        ~ConnectionManager();

        AutoPtr<Connection> getConnection(const std::string& connectionString);

        static ConnectionManager& get()
        {
            return instance;
        }

    private:
        static ConnectionManager instance;
    };

}