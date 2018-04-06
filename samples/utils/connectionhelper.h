#pragma once

namespace trader {

    class ConnectionHelper
    {
    public:
        void setupConnections(std::vector<std::string> _connections);
        void startConnections();
        void getConnections(std::vector<AutoPtr<trader::Interface::Connection>>& connections);
        AutoPtr<trader::Interface::Connection>& getConnection(const std::string& _connectionName);
        AutoPtr<trader::Interface::Connection> getAppConnection() { return appConnection; }
    protected:
        std::unordered_map<std::string, AutoPtr<trader::Interface::Connection>> connections;
        AutoPtr<trader::Interface::Connection> appConnection;
    };

}
