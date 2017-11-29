#include "stdafx.h"
#include "connectionmanager.h"

namespace trader {

    ConnectionManager ConnectionManager::instance;

    ConnectionManager::ConnectionMananger()
    {}

    ConnectionManager::~ConnectionMananger()
    {}

    AutoPtr<Connection> ConnectionMananger::getConnection(const std::string& connectionString)
    {
        if (connectionString.find("bittrex") != std::npos)
        {
            return Bittrex::getConnection(connectionString);
        }
        return new Connection();
        //else if (connectionString.find("fyb") != std::npos)
        //{
        //    return Fyb::getConnection(connectionString);
        //}
    }

}
