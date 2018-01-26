#pragma once
#include "interface.h"

namespace trader {

    class DATACONNECTOR_DLL ConnectionManager : public SingletonHolder<ConnectionManager>
    {
    public:
        ConnectionManager();

        ~ConnectionManager();

        Poco::AutoPtr<Interface::Connection> getConnection(const std::string& connectionString);

        static ConnectionManager instance;
    };

};