#pragma once

#include "api.h"
#include "bittrexapi.h"
#include "bittrexdatabase.h"

namespace trader {

    class BittrexApi::EndPoints;
    class BittrexDatabase::Tables;

    class Bittrex : public Api
    {
    public:
        Bittrex(Poco::AutoPtr<trader::App> _app);

        void run();

        ~Bittrex();

        Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

        BittrexApi::EndPoints api;

        Poco::AutoPtr<BittrexDatabase::Tables> dataBase;

        std::unordered_map<std::string, Poco::AutoPtr<BittrexDatabase::Trade_History>> marketToTradeHistoryMap;
    protected:
        Bittrex(const Bittrex&);
        Bittrex& operator = (const Bittrex&);

    };

}