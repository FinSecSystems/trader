#include "stdafx.h"
#include "connectionmanager.h"
#include "bittrex.h"
#include "fyb.h"
#include "kraken.h"
#include "cryptowatch.h"
#include "exchangeratelab.h"

namespace trader {

    ConnectionManager ConnectionManager::instance;

    AutoPtr<Interface::Connection> ConnectionData::getConnection(const std::string& connectionString)
    {
        AutoPtr<Interface::Connection> connection = nullptr;
        if (connectionString.find("bittrex") != std::string::npos)
        {
            connection = Bittrex::getConnection(connectionString);
        }
        else if (connectionString.find("cryptowatch") != std::string::npos)
        {
            connection = Cryptowatch::getConnection(connectionString);
        }
        else if (connectionString.find("kraken") != std::string::npos)
        {
            connection = Kraken::getConnection(connectionString);
        }
        else if (connectionString.find("fyb") != std::string::npos)
        {
            connection = Kraken::getConnection(connectionString);
        }
        else if (connectionString.find("exchangeratelab") != std::string::npos)
        {
            connection = Exchangeratelab::getConnection(connectionString);
        }
        else
        {
            return new Interface::CallConnection();
        }
        connections.push_back(connection);
        return connection;
    }

    void ConnectionData::start()
    {
        for (auto& connection : connections)
        {
            pool.startWithPriority(Thread::PRIO_LOWEST, *(Poco::Runnable*)connection.get() );
        }
    }

}
