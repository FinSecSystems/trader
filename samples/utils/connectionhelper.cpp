#include "stdafx.h"

#include "app.h"
#include "appconnection.h"
#include "connectionmanager.h"
#include "db.h"
#include "interface.h"
#include "connectionhelper.h"

namespace trader
{

    void ConnectionHelper::loadConnections()
    {
        AbstractConfiguration* appConfig = nullptr;
        try
        {
            appConfig = &Util::Application::instance().config();
        }
        catch (NullPointerException &)
        {
            Logger::get("Logs").information("Bad Application configuration: An application configuration is required to initialize the applications");
            return;
        }

        struct ConnectionParams
        {
            string name;
            string config;
            string getConnectionString()
            {
                ostringstream str;
                str << name << ";" << config;
                return str.str();
            }
        };

        std::vector<ConnectionParams> connectionParams;

        try
        {
            AutoPtr<AbstractConfiguration> pConnectionsConfig(appConfig->createView("app.connections"));
            AbstractConfiguration::Keys connectionConfigs;
            pConnectionsConfig->keys(connectionConfigs);
            for (AbstractConfiguration::Keys::const_iterator it = connectionConfigs.begin(); it != connectionConfigs.end(); ++it)
            {
                AutoPtr<AbstractConfiguration> pConnectionConfig(pConnectionsConfig->createView(*it));
                connectionParams.emplace_back();
                ConnectionParams& connectionParam = connectionParams.back();
                connectionParam.name = pConnectionConfig->getString("name");
                connectionParam.config = pConnectionConfig->getString("config");
            }
        }
        catch (Exception &exc)
        {
            Logger::get("Logs").information("Bad Application configuration: Invalid connection params",
                exc.message());
        }

        // Retrieve required connections from Connection Manager
        std::vector< std::string > connectionStrings;
        for (auto& connectionParam : connectionParams)
        {
            connectionStrings.push_back(connectionParam.getConnectionString());
        }
        setupConnections(connectionStrings);
    }

    void ConnectionHelper::setupAppConnection(ApplicationHelper* appHelper)
    {
        poco_assert(!appConnection);
        appConnection = new AppConnection(appHelper);
    }

    void ConnectionHelper::setupConnections(std::vector< std::string > _connections)
    {
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
