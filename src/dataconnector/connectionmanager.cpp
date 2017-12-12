#include "stdafx.h"
#include "connectionmanager.h"
#include "bittrex.h"
#include "fyb.h"
#include "kraken.h"
#include "cryptowatch.h"
#include "exchangeratelab.h"

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
        else if (connectionString.find("cryptowatch") != std::string::npos)
        {
            return Cryptowatch::getConnection(connectionString);
        }
        else if (connectionString.find("kraken") != std::string::npos)
        {
            return Kraken::getConnection(connectionString);
        }
        else if (connectionString.find("fyb") != std::string::npos)
        {
            return Kraken::getConnection(connectionString);
        }
        else if (connectionString.find("exchangeratelab") != std::string::npos)
        {
            return Exchangeratelab::getConnection(connectionString);
        }
        return new Interface::Connection();
        //else if (connectionString.find("fyb") != std::npos)
        //{
        //    return Fyb::getConnection(connectionString);
        //}
    }

}
