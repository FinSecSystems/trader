#pragma once

#include "api.h"
#include "cryptowatchapi.h"

namespace trader {

    class CryptowatchApi;

    class Cryptowatch : public Api
    {
    public:
        Cryptowatch(Poco::AutoPtr<trader::App> _app);

        ~Cryptowatch();

        Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

        CryptowatchApi api;

    protected:
        Cryptowatch(const Cryptowatch&);
        Cryptowatch& operator = (const Cryptowatch&);

    };

}