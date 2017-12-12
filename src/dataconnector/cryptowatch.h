#pragma once

#include "dataconnector/db.h"
#include "dataconnector/api.h"
#include "cryptowatchapi.h"
#include "cryptowatchdatabase.h"
#include "interface.h"

namespace trader {

    namespace CryptowatchApi {
        class EndPoints;
    };

    namespace CryptowatchDatabase {
        class Tables;
    };


    class Cryptowatch;

    class CryptowatchConnection : public Interface::Connection
    {
    public:
        CryptowatchConnection(const std::string& connectionid, Cryptowatch* _exchange)
            : exchange(_exchange)
        {
            (void)connectionid;
        }
    private:
        Cryptowatch* exchange;
    };

    class Cryptowatch : public Api
    {
    public:
        Cryptowatch();

        ~Cryptowatch();

        Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

        static AutoPtr<Interface::Connection> getConnection(const std::string& connectionId);

        CryptowatchApi::EndPoints api;

		Poco::AutoPtr<CryptowatchDatabase::Tables> dataBase;
    protected:
        Cryptowatch(const Cryptowatch&);
        Cryptowatch& operator = (const Cryptowatch&);

    };

}