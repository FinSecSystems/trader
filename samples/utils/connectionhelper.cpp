#include "stdafx.h"

#include "app.h"
#include "appconnection.h"
#include "connectionmanager.h"
#include "db.h"
#include "interface.h"
#include "connectionhelper.h"

namespace trader
{

    void ConnectionHelper::setupConnections(std::vector< std::string > _connections)
    {
        appConnection = new AppConnection((ApplicationHelper *)this);
        for (auto &connectionString : _connections)
        {
            auto it = connections.insert(
                {connectionString, ConnectionManager::instance.get()->getConnection(connectionString)});
            poco_assert(it.second);
            it.first->second->SetReceivingConnection(appConnection);
        }
    }

    AutoPtr< trader::Interface::Connection > &ConnectionHelper::getConnection(const std::string &_connectionName)
    {
        auto it = connections.find(_connectionName);
        if (it == connections.end())
        {
            // TODO: Throw
            poco_bugcheck();
            return it->second;
        }
        return it->second;
    }

    void ConnectionHelper::getConnections(std::vector< AutoPtr< trader::Interface::Connection > > &_ret_connections)
    {
        for (auto &connection : connections)
        {
            _ret_connections.push_back(connection.second);
        }
    }

    void ConnectionHelper::startConnections() { ConnectionManager::instance.get()->DoOperation(DC_START); }

} // namespace trader
