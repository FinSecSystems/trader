///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="bittrexconnection.cpp" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>BittrexConnection Class Implementation</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bittrex.h"
#include "app.h"
#include "bittrexapi.h"
#include "bittrexconnection.h"
#include "connectionmanager.h"

namespace trader
{

    using namespace BittrexApi;
    using namespace BittrexDatabase;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Gets a connection. </summary>
    ///
    /// <param name="connectionId"> Identifier for the connection. </param>
    ///
    /// <returns> The connection. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AutoPtr< Interface::Connection > BittrexConnection::getConnection(const std::string &connectionId)
    {
        return new BittrexConnection(connectionId, new Bittrex());
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Executes the operation operation. </summary>
    ///
    /// <param name="_operation"> The operation. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BittrexConnection::DoOperation(Poco::Int32 _operation)
    {
        switch (_operation)
        {
            case DC_START:
                ConnectionManager::instance.get()->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
                break;
			case DC_STOP:
				stop = true;
				break;

        }
    }

    /// <summary> Runs this object. </summary>
    void BittrexConnection::run()
    {
        processingConnection.RunMore();
        processingConnection.Run();
		if (!stop)
		{
			ConnectionManager::instance.get()->pool.startWithPriority(Thread::PRIO_LOWEST, *this);
		}
		else
		{
			stop = false;
		}
    }

    /// <summary> Executes the more operation. </summary>
    void BittrexProcessingConnection::RunMore()
    {
        for (auto &marketData : marketDataUpdateMap)
        {
            ProcessMessage(marketData.second.marketRequestData);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Security list request. </summary>
    ///
    /// <param name="securityListRequestData"> Information describing the security list request. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BittrexProcessingConnection::SecurityListRequest(
        Poco::AutoPtr< Interface::SecurityListRequestData > securityListRequestData)
    {
        static std::atomic< std::int32_t > idx = 0;

        Poco::AutoPtr< Interface::SecurityListData > securityListData = new Interface::SecurityListData();
        securityListData->setSourceConnection(connectionId);
        securityListData->securityListType = Interface::SecurityListType_MARKET;
        securityListData->securityReqID = securityListRequestData->securityReqID;
        securityListData->totNoRelatedSym = 0;
        securityListData->securityRequestResult = Interface::SecurityRequestResult_INVALID_OR_UNSUPPORTED_REQUEST;

        ostringstream str;
        str << "SL" << ++idx << endl;
        securityListData->securityResponseID = str.str();

        // Get Markets and create tables
        Poco::AutoPtr< BittrexApi::Markets > markets = exchange->api.GetMarkets();

        for (auto &market : markets->dataObject.result)
        {
            if (market.isActive && market.isSetMarketName())
            {
                securityListData->secListGrp.noRelatedSym.emplace_back();
                Interface::SecListGrpObject::NoRelatedSym &newMarket = securityListData->secListGrp.noRelatedSym.back();
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Gets unique response identifier. </summary>
    ///
    /// <returns> The unique response identifier. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string GetUniqueResponseId()
    {
        static std::atomic< std::int32_t > idx = 0;
        ostringstream uniqueResponseIdStream;
        uniqueResponseIdStream << "MD" << ++idx;
        return uniqueResponseIdStream.str();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Market data request. </summary>
    ///
    /// <param name="marketDataRequestData"> Information describing the market data request. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BittrexProcessingConnection::MarketDataRequest(
        Poco::AutoPtr< Interface::MarketDataRequestData > marketDataRequestData)
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
        // Poco::AutoPtr<MarketDataSnapshotFullRefresh> marketDataSnapshotFullRefreshData = new
        // MarketDataSnapshotFullRefresh();
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
        // Poco::AutoPtr<MarketDataIncrementalRefreshData> marketDataIncrementalRefreshData = new
        // MarketDataIncrementalRefreshData();
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

        bool updateOnly = (marketDataRequestData->subscriptionRequestType & UpdateBit) > 0;
        Poco::UInt32 subscriptionRequestType = marketDataRequestData->subscriptionRequestType & ~UpdateBit;

        if (subscriptionRequestType == Interface::SubscriptionRequestType_DISABLE_PREVIOUS_SNAPSHOT_PLUS_UPDATE_REQUEST)
        {
            poco_assert(updateOnly);
            MarketDataUpdateMap::iterator itFind = marketDataUpdateMap.find(marketDataRequestData->mDReqID);
            poco_assert(itFind != marketDataUpdateMap.end());
            marketDataUpdateMap.erase(itFind);
            return;
        }

        Poco::AutoPtr< Interface::MarketDataIncrementalRefreshData > marketDataIncrementalRefreshData;

        if (subscriptionRequestType == Interface::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES)
        {
            if (updateOnly)
            {
                marketDataIncrementalRefreshData = new Interface::MarketDataIncrementalRefreshData();
                marketDataIncrementalRefreshData->setSourceConnection(connectionId);
                marketDataIncrementalRefreshData->mDReqID = GetUniqueResponseId();
            }
            else
            {
                marketDataRequestData->subscriptionRequestType = (Interface::SubscriptionRequestType)(
                    ((Poco::UInt32)marketDataRequestData->subscriptionRequestType) | UpdateBit);
                MarketDataRequestRetrievalData data;
                data.marketRequestData = marketDataRequestData;
                marketDataUpdateMap.insert({marketDataRequestData->mDReqID, data});
            }
        }

        for (auto &sym : marketDataRequestData->instrmtMDReqGrp.noRelatedSym)
        {

            // Retrieve Trade History through REST API Call
            const std::string &marketName = sym.instrument.symbol;
            Poco::AutoPtr< HistoryParams > historyParams = new HistoryParams();
            historyParams->dataObject.SetMarket(marketName);
            AutoPtr< History > history = exchange->api.GetMarketHistory(historyParams);

            if (history->dataObject.result.size())
            {
                // Add market if it does not already exist
                SymIDMap::const_iterator marketExists = marketToTradeHistoryMap.find(marketName);
                if (marketExists == marketToTradeHistoryMap.end())
                {
                    BittrexMarketData marketData;
                    marketToTradeHistoryMap.insert({marketName, marketData});
                }

                // Save to in-memory cache
                BittrexMarketData &marketData = marketToTradeHistoryMap.find(marketName)->second;
                Int32 lastCachedId = marketData.lastCachedId;
                for (History::DataObject::Result::iterator it = history->dataObject.result.begin();
                     it != history->dataObject.result.end(); ++it)
                {
                    History::DataObject::ResultArray &trade = *it;
                    if (trade.id <= lastCachedId)
                    {
                        break;
                    }
                    marketData.marketDataMap.insert({trade.id, trade});
                    marketData.lastCachedId = std::max(marketData.lastCachedId, trade.id); // Update last cached id
                }

                if (!updateOnly)
                {
                    Poco::AutoPtr< Interface::MarketDataSnapshotFullRefreshData > marketDataSnapshotFullRefreshData =
                        new Interface::MarketDataSnapshotFullRefreshData();
                    marketDataSnapshotFullRefreshData->setSourceConnection(connectionId);
                    marketDataSnapshotFullRefreshData->instrument.symbol = marketName;
                    marketDataSnapshotFullRefreshData->mDReqID = GetUniqueResponseId();
                    marketDataSnapshotFullRefreshData->mDFullGrp.noMDEntries.reserve(marketData.marketDataMap.size());

                    for (auto itMap = marketData.marketDataMap.begin(); itMap != marketData.marketDataMap.end();
                         itMap++)
                    {
                        auto &marketDataItem = itMap->second;
                        marketDataSnapshotFullRefreshData->mDFullGrp.noMDEntries.emplace_back();
                        Interface::MDFullGrpObject::NoMDEntries &mdEntry =
                            marketDataSnapshotFullRefreshData->mDFullGrp.noMDEntries.back();
                        if (marketDataItem.orderType.compare("BUY") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_BID;
                        }
                        else if (marketDataItem.orderType.compare("SELL") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_OFFER;
                        }
                        else
                        {
                            Logger::get("Logs").error("Bittrex Error: Unknown order type %s", marketDataItem.orderType);
                            marketDataSnapshotFullRefreshData->mDFullGrp.noMDEntries.pop_back();
                            continue;
                        }

                        mdEntry.mDEntryPx = marketDataItem.price;
                        mdEntry.mDEntrySize = marketDataItem.quantity;
                        mdEntry.mDEntryTime = (Poco::Int32)marketDataItem.timeStamp.time;

                        mdEntry.ordType = Interface::OrdType_LIMIT;
                    }
                    receivingConnection->MarketDataSnapshotFullRefresh(marketDataSnapshotFullRefreshData);

                    if (subscriptionRequestType == Interface::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES)
                    {
                        MarketDataUpdateMap::iterator itFind = marketDataUpdateMap.find(marketDataRequestData->mDReqID);
                        MarketDataRequestRetrievalData &retrievalData = itFind->second;
                        retrievalData.lastCacheIdMap.insert({marketName, lastCachedId});
                    }
                }
                else
                {
                    MarketDataUpdateMap::iterator itFind = marketDataUpdateMap.find(marketDataRequestData->mDReqID);
                    MarketDataRequestRetrievalData &retrievalData = itFind->second;
                    MarketDataRequestRetrievalData::LastCacheIdMap::iterator itCache =
                        retrievalData.lastCacheIdMap.find(marketName);
                    Poco::Int32 &lastRetrievedId = itCache->second;

                    BittrexMarketData::MarketDataMap::iterator itMap;
                    if (itCache != retrievalData.lastCacheIdMap.end())
                    {
                        itMap = marketData.marketDataMap.find(lastRetrievedId);
                    }

                    for (; itMap != marketData.marketDataMap.end(); itMap++)
                    {
                        auto &marketDataItem = itMap->second;

                        marketDataIncrementalRefreshData->mDIncGrp.noMDEntries.emplace_back();
                        Interface::MDIncGrpObject::NoMDEntries &mdEntry =
                            marketDataIncrementalRefreshData->mDIncGrp.noMDEntries.back();

                        mdEntry.instrument.symbol = marketName;
                        if (marketDataItem.orderType.compare("BUY") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_BID;
                        }
                        else if (marketDataItem.orderType.compare("SELL") == 0)
                        {
                            mdEntry.mDEntryType = Interface::MDEntryType_OFFER;
                        }
                        else
                        {
                            Logger::get("Logs").error("Bittrex Error: Unknown order type %s", marketDataItem.orderType);
                            marketDataIncrementalRefreshData->mDIncGrp.noMDEntries.pop_back();
                            continue;
                        }

                        mdEntry.mDEntryPx = marketDataItem.price;
                        mdEntry.mDEntrySize = marketDataItem.quantity;
                        mdEntry.mDEntryTime = (Poco::Int32)marketDataItem.timeStamp.time;

                        mdEntry.ordType = Interface::OrdType_LIMIT;
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Creates a new order single. </summary>
    ///
    /// <param name="newOrderSingleData"> Information describing the new order single. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BittrexProcessingConnection::NewOrderSingle(Poco::AutoPtr< Interface::NewOrderSingleData > newOrderSingleData)
    {
        // [Server-Side]
        // Returns  TradeCaptureReport and/or ExecutionReport
        // TODO: Documentation

        // Example:

        // Poco::AutoPtr<ExecutionReportData> executionReportData = new ExecutionReportData();
        // receivingConnection->ExecutionReport(executionReportData);

        poco_bugcheck_msg("NewOrderSingle not implemented.");
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Order cancel request. </summary>
    ///
    /// <param name="orderCancelRequestData"> Information describing the order cancel request. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BittrexProcessingConnection::OrderCancelRequest(
        Poco::AutoPtr< Interface::OrderCancelRequestData > orderCancelRequestData)
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

    void BittrexProcessingConnection::TradeCaptureReportRequest(
        Poco::AutoPtr< Interface::TradeCaptureReportRequestData > tradeCaptureReportRequestData)
    {
        // [Server-Side]
        // Returns TradeCaptureReport
        // TODO: Documentation

        // Example:
        // Poco::AutoPtr<TradeCaptureReportData> tradeCaptureReportData = new TradeCaptureReportData();
        // receivingConnection->TradeCaptureReport(TradeCaptureReportData);

        poco_bugcheck_msg("TradeCaptureReportRequest not implemented.");
    }

} // namespace trader
