#pragma once
#include "interface.h"

namespace trader {

    class DATACONNECTOR_DLL ConnectionData
    {
    public:
        ThreadPool pool;
        std::vector<Poco::AutoPtr<Interface::Connection>> connections;
        Poco::AutoPtr<Interface::Connection> getConnection(const std::string& connectionString);
        void start();
    };

    class DATACONNECTOR_DLL ConnectionManager : public SingletonHolder<ConnectionData>
    {
    public:

        static ConnectionManager instance;
    };

};