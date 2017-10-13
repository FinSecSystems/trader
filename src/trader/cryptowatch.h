#pragma once

#include "api.h"
#include "cryptowatchapi.h"
#include "cryptowatchdatabase.h"

namespace trader {

    namespace CryptowatchApi {
        class EndPoints;
    };

    namespace CryptowatchDatabase {
        class Tables;
    };

    class Cryptowatch : public Api
    {
    public:
        Cryptowatch(Poco::AutoPtr<trader::App> _app);

        ~Cryptowatch();

        Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

        CryptowatchApi::EndPoints api;

		Poco::AutoPtr<CryptowatchDatabase::Tables> dataBase;
    protected:
        Cryptowatch(const Cryptowatch&);
        Cryptowatch& operator = (const Cryptowatch&);

    };

}