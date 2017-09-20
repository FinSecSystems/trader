#include "stdafx.h"
#include "bittrex.h"
#include "bittrexapi.h"
#include "helper.h"
#include "shautils.h"

namespace trader {

    using namespace BittrexApi;
    using namespace BittrexDatabase;

    Bittrex::Bittrex(Poco::AutoPtr<trader::App> _app)
        : api(_app, this)
        , dataBase(new BittrexDatabase::Tables(_app->dbSession))
    {
    }

    void Bittrex::run()
    {
        static bool useStorage = false;
        //Get Markets and create tables
        AutoPtr<Markets> balance = api.GetMarkets();
        for (auto& market : balance->dataObject.result)
        {
            if (market.isActive && market.isSetMarketName())
            {
                //Add market if it does not already exist
                std::unordered_map<std::string, MarketData>::const_iterator marketExists = marketToTradeHistoryMap.find(market.marketName);
                if (marketExists == marketToTradeHistoryMap.end())
                {
                    Poco::AutoPtr<Trade_History> tradeHistoryTable = new Trade_History(dataBase->db, market.marketName);
                    MarketData marketData;
                    marketData.storage = tradeHistoryTable;
                    marketToTradeHistoryMap.insert({ market.marketName, marketData });
                    if (useStorage)
                    {
                        tradeHistoryTable->init();
                    }
                }
            }
        }



        //Populate Trade History
        for (auto& market : marketToTradeHistoryMap)
        {
            //Retrieve Trade History through REST API Call
            const std::string& marketName = market.first;
            Poco::AutoPtr<HistoryParams> historyParams = new HistoryParams();
            historyParams->dataObject.SetMarket(marketName);
            AutoPtr<History> history = api.GetMarketHistory(historyParams);
            
            //Save to in-memory cache
            MarketData& marketData = market.second;
            Int32& lastCachedId = marketData.lastCachedId;
            for (History::DataObject::Result::reverse_iterator rit = history->dataObject.result.rbegin(); rit != history->dataObject.result.rend(); ++rit)
            {
                History::DataObject::ResultArray& trade = *rit;
                if (trade.id <= lastCachedId)
                {
                    break;
                }
                marketData.cache.insert({ trade.id, trade });
                lastCachedId = trade.id;
            }

            //Check pump

            static double ANALYSIS_INTERVAL_SECS = 30.0 * 60.0; // 30 minutes
            static double BUY_SELL_RATIO = 2.0; //2:1
            static double VOLUME_INCREASE = 1.0; //100%
            static double PRICE_INCREASE = 0.1; //10%

            time_t lastTimeStamp = 0;
            time_t oldestTimeStamp = 0;
            double totalVolumeRecent = 0;
            double totalVolumePrevious = 0;
            double latestPrice = 0;
            double oldestPrice = 0;
            Int32 numBuys = 0;
            Int32 numSells = 0;
            Int32 numEntries = 0;
            for (auto& order : marketData.cache)
            {
                BittrexApi::History::DataObject::ResultArray& trade = order.second;
                if (!lastTimeStamp)
                {
                    lastTimeStamp = trade.timeStamp.time;
                }
                if (std::difftime(trade.timeStamp.time, lastTimeStamp) > ANALYSIS_INTERVAL_SECS)
                {
                    break;
                }
                if (!latestPrice)
                {
                    latestPrice = trade.price;
                }
                oldestPrice = trade.price;
                if (std::difftime(trade.timeStamp.time, lastTimeStamp) < ANALYSIS_INTERVAL_SECS/2)
                {
                    totalVolumeRecent += trade.quantity;
                }
                else
                {
                    totalVolumePrevious += trade.quantity;
                }
                if (trade.orderType.compare("SELL") == 0)
                {
                    numSells++;
                }
                if (trade.orderType.compare("BUY") == 0)
                {
                    numBuys++;
                }
                numEntries++;
                oldestTimeStamp = trade.timeStamp.time;
            }

            char recentTime[20];
            strftime(recentTime, 20, "%Y-%m-%d %H:%M:%S", localtime(&lastTimeStamp));
            char oldestTime[20];
            strftime(oldestTime, 20, "%Y-%m-%d %H:%M:%S", localtime(&oldestTimeStamp));

            printf("%s: Oldest Time %s, Newest Time %s, Num Entries %d\n", marketName.c_str(), oldestTime, recentTime, numEntries);

            double buySellRatio = numBuys / (numSells > 0 ? numSells : 1 ) ;
            if (buySellRatio >= BUY_SELL_RATIO)
            {
                printf("%s: Buy sell ratio %f\n", marketName.c_str(), buySellRatio);
            }

            double volumeIncrease = (totalVolumeRecent - totalVolumePrevious) / totalVolumePrevious;
            if (totalVolumePrevious > 0 && volumeIncrease > VOLUME_INCREASE)
            {
                printf("%s: Volume Increase %2.2f\n", marketName.c_str(), volumeIncrease*100.0);
            }

            double priceIncrease = (latestPrice - oldestPrice) / oldestPrice;
            if (priceIncrease > PRICE_INCREASE)
            {
                printf("%s: Price Increase %2.2f\n", marketName.c_str(), priceIncrease*100.0);
            }

//            break;

            if (useStorage)
            {
                //Save to storage
                Trade_History& table = *marketData.storage;
                Trade_History::RecordWithId latestRec;
                table.getLatest(latestRec);

                Int32 latestStoredTradeId = 0;
                if (latestRec.isSetTradeId())
                {
                    latestStoredTradeId = latestRec.tradeId;
                }

                std::vector<Trade_History::Record> records;
                for (History::DataObject::Result::reverse_iterator rit = history->dataObject.result.rbegin(); rit != history->dataObject.result.rend(); ++rit)
                {
                    History::DataObject::ResultArray& trade = *rit;
                    if (trade.id <= latestStoredTradeId)
                    {
                        break;
                    }
                    Trade_History::Record rec;
                    rec.tradeId = trade.id;
                    rec.orderType = trade.orderType;
                    rec.price = trade.price;
                    rec.total = trade.total;
                    rec.volume = trade.quantity;
                    rec.fillType = trade.filltype;
                    rec.timeStamp = (Int32)trade.timeStamp.time;
                    records.push_back(rec);
                }
                if (!records.empty())
                {
                    table.insertMultipleUnique(records);
                }
            }
        }
    }

    Bittrex::~Bittrex()
    {
    }

	string getHMAC2(string keyParam, string message)
	{
		char key[10000];
		char data[10000];
		strcpy(key, keyParam.c_str());
		strncpy(data, message.c_str(), sizeof(data));

		unsigned char* digest;
		digest = HMAC(EVP_sha512(), key, (int)strlen(key), (unsigned char*)data, (int)strlen(data), NULL, NULL);
		char mdString[SHA512_DIGEST_LENGTH*2+1];
		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
			sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
		mdString[SHA512_DIGEST_LENGTH * 2] = '\0';

		string output = mdString;
		return output;
	}

    Dynamic::Var Bittrex::invoke(const string& httpMethod, URI& uri)
    {
        (void)httpMethod;

		time_t currentTimeStamp = std::time(nullptr);

		bool privateApi = (uri.getHost().find("public") == std::string::npos);

		// Sign request
		if (privateApi)
		{
			//Add api key
			uri.addQueryParameter(string("apikey"), api.config.dataObject.api_key);

			//Add nonce
			ostringstream nonceStream;
			nonceStream << currentTimeStamp;
			uri.addQueryParameter(string("nonce"), nonceStream.str());
		}

        // Create the request URI.
        HTTPSClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);

		if (privateApi)
		{
			req.set("apisign", getHMAC2(api.config.dataObject.api_secret, uri.toString()));
		}

		//Submit
		session.sendRequest(req);

        Logger::get("Logs").information("Send Request: %s", uri.toString());

        // Receive the response.
        HTTPResponse res;
        istream& rs = session.receiveResponse(res);

        // Parse the JSON
        JSON::Parser parser;
        parser.parse(rs);
        Dynamic::Var result = parser.result();
        string resultString = Dynamic::Var::toString(result);
        Logger::get("Logs").information("Received Response: %s", resultString);

        // If everything went fine, return the JSON document.
        // Otherwise throw an exception.
        if (res.getStatus() == HTTPResponse::HTTP_OK)
        {
            Poco::AutoPtr<ResultIntrospector> msg = new ResultIntrospector();
            msg->read(result);
            if (!msg->dataObject.success)
            {
                throw ApplicationException("Bittrex Error", "Received Error Response");
            }
            return result;
        }
        else
        {
            throw ApplicationException("Bittrex Error", "");
        }
    }
}
