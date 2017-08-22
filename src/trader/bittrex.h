#pragma once

#include "api.h"
#include "bittrexapi.h"

namespace trader {

    class BittrexApi::EndPoints;

    class Bittrex : public Api
    {
    public:
        Bittrex(Poco::AutoPtr<trader::App> _app);

        ~Bittrex();

        Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

        BittrexApi::EndPoints api;

    protected:
        Bittrex(const Bittrex&);
        Bittrex& operator = (const Bittrex&);

    };

}