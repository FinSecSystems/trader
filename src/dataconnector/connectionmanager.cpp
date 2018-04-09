#include "stdafx.h"
#include "connectionmanager.h"
#include "bittrex.h"
#include "cryptowatch.h"
#include "exchangeratelab.h"
#include "fyb.h"
#include "kraken.h"

namespace trader
{

    ConnectionManager ConnectionManager::instance;

    AutoPtr< Interface::Connection > ConnectionData::getConnection(const std::string &connectionString)
    {
        AutoPtr< Interface::Connection > connection = nullptr;
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
        connection->SetName(connectionString);
        connections.insert({connectionString, connection});
        return connection;
    }

    void ConnectionData::DoOperation(DataConnectorOperation _operation)
    {
        switch (_operation)
        {
            case DC_START:
                for (auto &connectionPair : connections)
                {
                    Poco::AutoPtr< trader::Interface::Connection > connection = connectionPair.second;
                    connection->DoOperation(_operation);
                }
                break;
        }
    }

} // namespace trader
