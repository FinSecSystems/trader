///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="bittrexconnection.h" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Declares the API class</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "api.h"
#include "app.h"
#include "bittrexapi.h"
#include "bittrexdatabase.h"
#include "db.h"
#include "interface.h"
#include "interfacehelper.h"
#include "bittrex.h"

namespace trader
{

    /// <summary> A bittrex processing connection. </summary>
    class BittrexProcessingConnection : public Interface::MessageReceivingConnection
    {
      public:
        BittrexProcessingConnection() {}

        /// <summary>
        /// [Client-Side] Get a list of securities that can be traded on the exchange.
        /// </summary>
        /// <param name="securityListRequestData">Request Data</param>
        /// <param name="securityListRequestData.SecurityReqID">Unique identifier of this request.</param>
        void SecurityListRequest(Poco::AutoPtr< Interface::SecurityListRequestData > securityListRequestData) override;

        /// <summary>
        /// [Client-Side] Subscribes the current session to a Market Data - Snapshot/Full Refresh
        /// followed by zero or more Market Data - Incremental Refresh messages.
        /// </summary>
        /// <param name="marketDataRequestData">Market Data Request Params</param>
        /// <param name="marketDataRequestData.MDReqID">Unique identifier of the market data request.Uniqueness must be
        /// guaranteed by the institution for the duration of the connection to the market data channel.</param> <param
        /// name="marketDataRequestData.SubscriptionRequestType">Indicates what type of response is expected.
        ///              Valid Value: 1 = Snapshot + Updates(Subscribe)
        /// </param>
        /// <param name="marketDataRequestData.MarketDepth">Depth of the book to receive snapshot and updates
        /// for.</param>
        ///              Valid Value: 0 = Full Book, 1 = Top of Book
        /// </param>
        /// <param name="marketDataRequestData.NoMDEntryTypes">Number of MDEntryType fields requested</param>
        /// <param name="marketDataRequestData.MDEntryType">Type of market data entry to receive snapshots and updates
        /// for.</param>
        ///              Valid values : 0 = Bid
        ///                             1 = Offer
        ///                             2 = Trade
        ///                             Q = Auction Clearing Price
        /// </param>
        /// <param name="marketDataRequestData.NoRelatedSym">Number of symbols requested.</param>
        /// <param name="marketDataRequestData.Symbol">Market data symbol requested.
        ///                                            Valid Values : See Security List for a list of supported symbols.
        /// </param>
        void MarketDataRequest(Poco::AutoPtr< Interface::MarketDataRequestData > marketDataRequestData) override;

        /// <summary>
        /// [Client-Side] Submit a new order to exchange
        /// </summary>
        /// <param name="newOrderSingleData">New Order Single Data Params</param>
        /// <param name="newOrderSingleData.ClOrdID">Unique identifier of the order as assigned by the institution.
        /// Uniqueness must be guaranteed by the institution for the duration of the connection to the order entry
        /// channel.</param> <param name="newOrderSingleData.ExecInst">[Optional]Specifies that an order should be
        /// Maker-or-Cancel, TimeInForce must be 1 (Good Till Cancel)
        ///                                           Valid Value: 6 = Participate don't initiate (maker-or-cancel)
        /// </param>
        /// <param name="newOrderSingleData.OrderQty">Decimal amount of security to purchase. Full quantity will be
        /// visible on the book.</param> <param name="newOrderSingleData.OrdType">Order Type, Valid Value: 2 =
        /// Limit</param> <param name="newOrderSingleData.Price">[Optional]Decimal amount of USD to spend per
        /// Security.</param>
        ///                                        Price is required when OrdTyp is 2 = Limit.
        /// </param>
        /// <param name="newOrderSingleData.Side">Side of the order.
        ///                                       Valid Value: 1 = Buy, 2 = Sell
        /// </param>
        /// <param name="newOrderSingleData.Symbol">Market data symbol requested.
        ///                                         Valid Values : See Security List for a list of supported symbols.
        /// </param>
        /// <param name="newOrderSingleData.TimeInForce">Specifies how long the order remains in effect. Use 7 (At the
        /// close) for Auction orders
        ///                                              Valid Values : 1 = Good Till Cancel (GTC)
        ///                                                             3 = Immediate Or Cancel (IOC)
        /// </param>
        /// <param name="newOrderSingleData.TransactTime">Time of order creation(expressed in UTC).</param>
        void NewOrderSingle(Poco::AutoPtr< Interface::NewOrderSingleData > newOrderSingleData) override;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> TODO: Documentation. </summary>
        ///
        /// <param name="orderCancelRequestData"> Information describing the order cancel request. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void OrderCancelRequest(Poco::AutoPtr< Interface::OrderCancelRequestData > orderCancelRequestData) override;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> TODO: Documentation. </summary>
        ///
        /// <param name="tradeCaptureReportRequestData"> Information describing the trade capture report request. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void TradeCaptureReportRequest(
            Poco::AutoPtr< Interface::TradeCaptureReportRequestData > tradeCaptureReportRequestData) override;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Sets connection identifier. </summary>
        ///
        /// <param name="_connectionId"> Identifier for the connection. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetConnectionId(const std::string &_connectionId) { connectionId = _connectionId; }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Sets an exchange. </summary>
        ///
        /// <param name="_exchange"> [in,out] If non-null, the exchange. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetExchange(Bittrex *_exchange) { exchange = _exchange; }

        /// <summary> Executes the more operation. </summary>
        void RunMore();

        Bittrex *exchange;

        std::string connectionId;

        /// <summary> In-memory cache of marketdata. </summary>
        struct BittrexMarketData
        {
            /// <summary> Initializes a new instance of the bittrexconnection class. </summary>
            BittrexMarketData()
                : lastCachedId(0)
            {
            }
            /// <summary> Defines an alias representing the market data map. </summary>
            typedef std::unordered_map< Poco::Int32, BittrexApi::History::DataObject::ResultArray > MarketDataMap;
            MarketDataMap marketDataMap;	///< The market data map
            Poco::Int32 lastCachedId;   ///< Identifier for the last cached
        };

        /// <summary> Defines an alias representing the symbol identifier map. </summary>
        typedef std::unordered_map< std::string, BittrexMarketData > SymIDMap;
        SymIDMap marketToTradeHistoryMap;   ///< The market to trade history map

        /// <summary> A market data request retrieval data. </summary>
        struct MarketDataRequestRetrievalData
        {
            Poco::AutoPtr< Interface::MarketDataRequestData > marketRequestData;	///< Information describing the market request

            /// <summary> The id of the last marketData entry that was sent to the requester. </summary>
            typedef std::unordered_map< std::string, Poco::Int32 > LastCacheIdMap;
            LastCacheIdMap lastCacheIdMap;  ///< The last cache identifier map
        };

        /// <summary> Defines an alias representing the market data update map. </summary>
        typedef std::unordered_map< std::string, MarketDataRequestRetrievalData > MarketDataUpdateMap;
        MarketDataUpdateMap marketDataUpdateMap;	///< The market data update map
    };

    class BittrexConnection : public Interface::CallConnection, public Poco::Runnable
    {
    public:
        BittrexConnection(const std::string &_connectionid, Bittrex *_exchange)
            : processingConnection(10)
			, stop(false)
        {
            processingConnection.SetConnectionId(_connectionid);
            processingConnection.SetExchange(_exchange);
        }

        void ProcessMessage(Poco::AutoPtr< Interface::IMessageData > _messageData) override
        {
            processingConnection.ProcessMessage(_messageData);
        }

        void SetReceivingConnection(Poco::AutoPtr< Interface::Connection > _connection) override
        {
            processingConnection.SetReceivingConnection(_connection);
        }

        void run() override;

        void DoOperation(Poco::Int32 operation) override;

        BufferedConnection< BittrexProcessingConnection > processingConnection;

		bool stop;
        static AutoPtr< Interface::Connection > getConnection(const std::string &connectionId);
    };

} // namespace trader
