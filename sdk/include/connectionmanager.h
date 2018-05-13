#pragma once
#include "interface.h"
#include <map>

namespace trader
{

    class DATACONNECTOR_DLL ConnectionData
    {
      public:
        ThreadPool pool;
        std::map< std::string, Poco::AutoPtr< Interface::Connection > > connections;
        Poco::AutoPtr< Interface::Connection > getConnection(const std::string &connectionString);
        void DoOperation(DataConnectorOperation _operation);
    };

    class DATACONNECTOR_DLL ConnectionManager : public SingletonHolder< ConnectionData >
    {
      public:
        static ConnectionManager instance;
    };

}; // namespace trader
