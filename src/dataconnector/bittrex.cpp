#include "stdafx.h"
#include "bittrex.h"
#include "bittrexapi.h"
#include "helper.h"
#include "shautils.h"
#include "app.h"
#include "connectionmanager.h"

namespace trader {

    using namespace BittrexApi;
    using namespace BittrexDatabase;

    AutoPtr<Interface::Connection> Bittrex::getConnection(const std::string& connectionId)
    {
        return new BittrexConnection(connectionId, new Bittrex());
    }

    Bittrex::Bittrex()
        : api(AppManager::instance.get()->getApp(), this)
        , dataBase(new BittrexDatabase::Tables(DbManager::instance.getDb()->getDbSession()))
    {
    }
    
    void Bittrex::run()
    {
#if 0
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

            break;

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
#endif
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

    void BittrexConnection::DoOperation(Poco::Int32 _operation)
    {
        switch (_operation)
        {
        case DC_START:
            ConnectionManager::instance.get()->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
            break;
        }
    }

    void BittrexConnection::run()
    {
        processingConnection.RunMore();
        processingConnection.Run();
        ConnectionManager::instance.get()->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
    }

    void BittrexProcessingConnection::RunMore()
    {
        for (auto& marketData : marketDataUpdateMap)
        {
            ProcessMessage(marketData.second.marketRequestData);
        }
    }

    void BittrexProcessingConnection::SecurityListRequest(Poco::AutoPtr<SecurityListRequestData> securityListRequestData)
    {
        static  std::atomic<std::int32_t> idx = 0;

        Poco::AutoPtr<SecurityListData> securityListData = new SecurityListData();
        securityListData->setSourceConnection(connectionId);
        securityListData->securityListType = Interface::SecurityListType_MARKET;
        securityListData->securityReqID = securityListRequestData->securityReqID;
        securityListData->totNoRelatedSym = 0;
        securityListData->securityRequestResult = Interface::SecurityRequestResult_INVALID_OR_UNSUPPORTED_REQUEST;

        ostringstream str;
        str << "SL" << ++idx << endl;
        securityListData->securityResponseID = str.str();

        //Get Markets and create tables
        Poco::AutoPtr<BittrexApi::Markets> markets = exchange->api.GetMarkets();

        for (auto& market : markets->dataObject.result)
        {
            if (market.isActive && market.isSetMarketName())
            {
                securityListData->secListGrp.noRelatedSym.emplace_back();
                Interface::SecListGrpObject::NoRelatedSym& newMarket = securityListData->secListGrp.noRelatedSym.back();
                newMarket.instrument.symbol = market.marketName;
                securityListData->totNoRelatedSym++;
            }
        }

        if (securityListData->totNoRelatedSym != 0)
        {
            securityListData->securityRequestResult = Interface::SecurityRequestResult_VALID_REQUEST;
        }

        receivingConnection->SecurityList(securityListData);
    }


    std::string GetUniqueResponseId()
    {
        static  std::atomic<std::int32_t> idx = 0;
        ostringstream uniqueResponseIdStream;
        uniqueResponseIdStream << "MD" << ++idx;
        return uniqueResponseIdStream.str();
    }

    void BittrexProcessingConnection::MarketDataRequest(Poco::AutoPtr<MarketDataRequestData> marketDataRequestData)
    {
        // [Server-Side]
        // Returns either MarketDataSnapshotFullRefreshData, MarketDataIncrementalRefresh or MarketDataRequestReject

        // MarketDataSnapshotFullRefresh
        // MDReqID - Unique identifier of the Market Data Request this message is in response to.
        // Symbol - Symbol of market data entry.
        // NoMDEntries - Number of entries in this message.
        //             - MDEntryType - Type of market data update.
        //                           - Valid values : 0 = Bid
        //                                            1 = Offer
        //                                            2 = Trade
        //              - MDEntryPx	- Price of market data entry.
        //              - MDEntrySize - Quantity of market data entry.
        // Example:
        // Poco::AutoPtr<MarketDataSnapshotFullRefresh> marketDataSnapshotFullRefreshData = new MarketDataSnapshotFullRefresh();
        // receivingConnection->MarketDataSnapshotFullRefresh(marketDataSnapshotFullRefreshData);

        // MarketDataIncrementalRefresh
        // MDReqID - Unique identifier of the Market Data Request this message is in response to.
        // Symbol - Symbol of market data entry.
        // NoMDEntries - Number of entries in this message.
        //             - MDUpdateAction - Type of market data update.
        //                              - Valid values : 0 = New
        //                                               1 = Change
        //                                               2 = Delete
        //             - MDEntryType - Type of market data update.
        //                           - Valid values : 0 = Bid
        //                                            1 = Offer
        //                                            2 = Trade
        //             - MDEntryPx	- Price of market data entry.
        //             - MDEntrySize - Quantity of market data entry.
        // Example:
        // Poco::AutoPtr<MarketDataIncrementalRefreshData> marketDataIncrementalRefreshData = new MarketDataIncrementalRefreshData();
        // receivingConnection->MarketDataIncrementalRefresh(marketDataIncrementalRefreshData);

        // MarketDataRequestReject
        // MDReqID - Unique identifier of the Market Data Request this message is in response to.
        // MDReqRejReason - Reason why Market Data Request was rejected.
        //                - Valid values : 0 = Unknown Symbol
        //                                 1 = Duplicate MDReqID
        //                                 4 = Unsupported SubscriptionRequestType
        //                                 5 = Unsupported MarketDepth
        //                                 8 = Unsupported MDEntryType
        // Example:
        // Poco::AutoPtr<MarketDataRequestRejectData> marketDataRequestRejectData = new MarketDataRequestReject();
        // receivingConnection->MarketDataRequestReject(marketDataRequestRejectData);

        const Poco::UInt32 UpdateBit = 0x80000000;

        bool updateOnly = ( marketDataRequestData->subscriptionRequestType & UpdateBit ) > 0;
        Poco::UInt32 subscriptionRequestType = marketDataRequestData->subscriptionRequestType & ~UpdateBit;

        if (subscriptionRequestType == Interface::SubscriptionRequestType_DISABLE_PREVIOUS_SNAPSHOT_PLUS_UPDATE_REQUEST)
        {
            poco_assert(updateOnly);
            MarketDataUpdateMap::iterator itFind = marketDataUpdateMap.find(marketDataRequestData->mDReqID);
            poco_assert(itFind != marketDataUpdateMap.end());
            marketDataUpdateMap.erase(itFind);

        }

        Poco::AutoPtr<Interface::IConnection::MarketDataIncrementalRefreshData> marketDataIncrementalRefreshData;

        if (subscriptionRequestType == Interface::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES)
        {
            marketDataIncrementalRefreshData = new Interface::IConnection::MarketDataIncrementalRefreshData();
            marketDataIncrementalRefreshData->setSourceConnection(connectionId);
            marketDataIncrementalRefreshData->mDReqID = GetUniqueResponseId();
            if (!updateOnly)
            {
                marketDataRequestData->subscriptionRequestType = (Interface::SubscriptionRequestType) ( ((Poco::UInt32) marketDataRequestData->subscriptionRequestType) | UpdateBit );
                MarketDataRequestRetrievalData data;
                data.marketRequestData = marketDataRequestData;
                marketDataUpdateMap.insert({ marketDataRequestData->mDReqID, data });
            }
        }

        for (auto& sym : marketDataRequestData->instrmtMDReqGrp.noRelatedSym)
        {

            //Retrieve Trade History through REST API Call
            const std::string& marketName = sym.instrument.symbol;
            Poco::AutoPtr<HistoryParams> historyParams = new HistoryParams();
            historyParams->dataObject.SetMarket(marketName);
            AutoPtr<History> history = exchange->api.GetMarketHistory(historyParams);

            if (history->dataObject.result.size())
            {
                //Add market if it does not already exist
                SymIDMap::const_iterator marketExists = marketToTradeHistoryMap.find(marketName);
                if (marketExists == marketToTradeHistoryMap.end())
                {
                    BittrexMarketData marketData;
                    marketToTradeHistoryMap.insert({ marketName, marketData });
                }

                //Save to in-memory cache
                BittrexMarketData& marketData = marketToTradeHistoryMap.find(marketName)->second;
                Int32 lastCachedId = marketData.lastCachedId;
                for (History::DataObject::Result::reverse_iterator rit = history->dataObject.result.rbegin(); rit != history->dataObject.result.rend(); ++rit)
                {
                    History::DataObject::ResultArray& trade = *rit;
                    if (trade.id <= lastCachedId)
                    {
                        break;
                    }
                    marketData.marketDataMap.insert({ trade.id, trade });
                    marketData.lastCachedId = std::max(marketData.lastCachedId, trade.id); //Update last cached id
                }

                if (!updateOnly)
                {
                    Poco::AutoPtr<Interface::IConnection::MarketDataSnapshotFullRefreshData> marketDataSnapshotFullRefreshData = new Interface::IConnection::MarketDataSnapshotFullRefreshData();
                    marketDataSnapshotFullRefreshData->setSourceConnection(connectionId);
                    marketDataSnapshotFullRefreshData->instrument.symbol = marketName;
                    marketDataSnapshotFullRefreshData->mDReqID = GetUniqueResponseId();
                    marketDataSnapshotFullRefreshData->mDFullGrp.noMDEntries.reserve(marketData.marketDataMap.size());
                    BittrexMarketData::MarketDataMap::iterator itMap = marketData.marketDataMap.begin();
                    Interface::MDFullGrpObject::NoMDEntriesArray::iterator itVec = marketDataSnapshotFullRefreshData->mDFullGrp.noMDEntries.begin();
                    for (;itMap != marketData.marketDataMap.end();itMap++,itVec++)
                    {
                        auto& marketDataItem = itMap->second;
                        auto& mdEntry = *itVec;
                        if (marketDataItem.orderType.compare("bid")==0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_BID;
                        }
                        else if (marketDataItem.orderType.compare("offer") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_OFFER;
                        }
                        else if (marketDataItem.orderType.compare("trade") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_TRADE;
                        }
                        else
                        {
                            poco_bugcheck_msg("Unknown");
                        }

                        mdEntry.mDEntryPx   = marketDataItem.price;
                        mdEntry.mDEntrySize = marketDataItem.quantity;
                        mdEntry.mDEntryTime = (Poco::Int32)marketDataItem.timeStamp.time;

                        if (marketDataItem.filltype.compare("limit") == 0)
                        {
                            mdEntry.ordType = Interface::OrdType_LIMIT;
                        }
                    }
                    receivingConnection->MarketDataSnapshotFullRefresh(marketDataSnapshotFullRefreshData);

                    if (subscriptionRequestType == Interface::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES)
                    {
                        MarketDataUpdateMap::iterator itFind = marketDataUpdateMap.find(marketDataRequestData->mDReqID);
                        MarketDataRequestRetrievalData& retrievalData = itFind->second;
                        retrievalData.lastCacheIdMap.insert({ marketName, lastCachedId });
                    }
                }
                else
                {
                    MarketDataUpdateMap::iterator itFind = marketDataUpdateMap.find(marketDataRequestData->mDReqID);
                    MarketDataRequestRetrievalData& retrievalData = itFind->second;
                    MarketDataRequestRetrievalData::LastCacheIdMap::iterator itCache = retrievalData.lastCacheIdMap.find(marketName);
                    Poco::Int32& lastRetrievedId = itCache->second;

                    BittrexMarketData::MarketDataMap::iterator itMap;
                    if (itCache != retrievalData.lastCacheIdMap.end())
                    {
                        itMap = marketData.marketDataMap.find(lastRetrievedId);
                    }

                    for (;itMap != marketData.marketDataMap.end();itMap++)
                    {
                        auto& marketDataItem = itMap->second;

                        marketDataIncrementalRefreshData->mDIncGrp.noMDEntries.emplace_back();
                        Interface::MDIncGrpObject::NoMDEntries& mdEntry = marketDataIncrementalRefreshData->mDIncGrp.noMDEntries.back();

                        mdEntry.instrument.symbol = marketName;
                        if (marketDataItem.orderType.compare("bid") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_BID;
                        }
                        else if (marketDataItem.orderType.compare("offer") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_OFFER;
                        }
                        else if (marketDataItem.orderType.compare("trade") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_TRADE;
                        }
                        else
                        {
                            poco_bugcheck_msg("Unknown");
                        }

                        mdEntry.mDEntryPx = marketDataItem.price;
                        mdEntry.mDEntrySize = marketDataItem.quantity;
                        mdEntry.mDEntryTime = (Poco::Int32)marketDataItem.timeStamp.time;

                        if (marketDataItem.filltype.compare("limit") == 0)
                        {
                            mdEntry.ordType = Interface::OrdType_LIMIT;
                        }
                    }

                    lastRetrievedId = marketData.lastCachedId;
                }

            }

        }

        if (updateOnly)
        {
            receivingConnection->MarketDataIncrementalRefresh(marketDataIncrementalRefreshData);
        }

    }


    void BittrexProcessingConnection::NewOrderSingle(Poco::AutoPtr<NewOrderSingleData> newOrderSingleData)
    {
        // [Server-Side]
        // Returns  TradeCaptureReport and/or ExecutionReport
        // TODO: Documentation

        // Example:

        // Poco::AutoPtr<ExecutionReportData> executionReportData = new ExecutionReportData();
        // receivingConnection->ExecutionReport(executionReportData);

        poco_bugcheck_msg("NewOrderSingle not implemented.");
    }

    void BittrexProcessingConnection::OrderCancelRequest(Poco::AutoPtr<OrderCancelRequestData> orderCancelRequestData)
    {
        // [Server-Side]
        // Returns ExecutionReport or OrderCancelReject
        // TODO: Documentation

        // Example:
        // Poco::AutoPtr<ExecutionReportData> executionReportData = new ExecutionReportData();
        // clientConnection->ExecutionReport(executionReportData);
        // Poco::AutoPtr<OrderCancelRejectData> orderCancelRejectData = new OrderCancelRejectData();
        // receivingConnection->OrderCancelReject(orderCancelRejectData);

        poco_bugcheck_msg("OrderCancelRequest not implemented.");
    }

    void BittrexProcessingConnection::TradeCaptureReportRequest(Poco::AutoPtr<TradeCaptureReportRequestData> tradeCaptureReportRequestData)
    {
        // [Server-Side]
        // Returns TradeCaptureReport
        // TODO: Documentation

        // Example:
        // Poco::AutoPtr<TradeCaptureReportData> tradeCaptureReportData = new TradeCaptureReportData();
        // receivingConnection->TradeCaptureReport(TradeCaptureReportData);

        poco_bugcheck_msg("TradeCaptureReportRequest not implemented.");
    }

}
