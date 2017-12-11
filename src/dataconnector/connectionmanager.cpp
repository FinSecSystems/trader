#include "stdafx.h"
#include "connectionmanager.h"
#include "bittrex.h"

namespace trader {

    //ConnectionManager ConnectionManager::instance;

    ConnectionManager::ConnectionManager()
    {}

    ConnectionManager::~ConnectionManager()
    {}

    AutoPtr<Interface::Connection> ConnectionManager::getConnection(const std::string& connectionString)
    {
        if (connectionString.find("bittrex") != std::string::npos)
        {
            return Bittrex::getConnection(connectionString);
        }
        return new Interface::Connection();
        //else if (connectionString.find("fyb") != std::npos)
        //{
        //    return Fyb::getConnection(connectionString);
        //}
    }

}
