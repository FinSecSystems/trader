///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="connectionmanager.cpp" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>ConnectionManager Implementation</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "connectionmanager.h"
#include "bittrexconnection.h"
#include "cryptowatch.h"
#include "exchangeratelab.h"
#include "fyb.h"
#include "kraken.h"

namespace trader
{

    ConnectionManager ConnectionManager::instance;  ///< The connection manager instance

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Gets a connection. </summary>
    ///
    /// <param name="connectionString"> The connection string. </param>
    ///
    /// <returns> The connection. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AutoPtr< Interface::Connection > ConnectionData::getConnection(const std::string &connectionString)
    {
        AutoPtr< Interface::Connection > connection = nullptr;
        if (connectionString.find("bittrex") != std::string::npos)
        {
            connection = BittrexConnection::getConnection(connectionString);
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Executes the operation operation. </summary>
    ///
    /// <param name="_operation"> The operation. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void ConnectionData::DoOperation(DataConnectorOperation _operation)
    {
		for (auto &connectionPair : connections)
		{
			Poco::AutoPtr< trader::Interface::Connection > connection = connectionPair.second;
			connection->DoOperation(_operation);
		}

		switch (_operation)
        {
            case DC_START:
				break;
			case DC_STOP:
				pool.joinAll();
                break;
        }
    }

} // namespace trader
