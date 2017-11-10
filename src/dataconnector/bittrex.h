#pragma once

#include "dataconnector/db.h"
#include "dataconnector/api.h"
#include "bittrexapi.h"
#include "bittrexdatabase.h"

namespace trader {

    namespace BittrexApi {
        class EndPoints;
    };

    namespace BittrexDatabase {
        class Tables;
    };

    class Bittrex : public Api
    {
    public:
        Bittrex(Poco::AutoPtr<trader::Db> _app);

        void run();

        ~Bittrex();

        Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

        BittrexApi::EndPoints api;

        Poco::AutoPtr<BittrexDatabase::Tables> dataBase;

        struct MarketData
        {
            MarketData()
                : lastCachedId(0)
            {}
            Poco::AutoPtr<BittrexDatabase::Trade_History> storage;
            std::map<Poco::Int32, BittrexApi::History::DataObject::ResultArray> cache;
            Poco::Int32 lastCachedId;
        };

        std::unordered_map<std::string, MarketData> marketToTradeHistoryMap;
    protected:
        Bittrex(const Bittrex&);
        Bittrex& operator = (const Bittrex&);

    };

}