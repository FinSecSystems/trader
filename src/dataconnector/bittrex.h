// ***********************************************************************
// Assembly         : trader
// Author           : Viknash
// ***********************************************************************
// <copyright file="bittrex.h" >
//     Copyright (c) FinSec Systems. All rights reserved.
// </copyright>
// <summary>
//     Communication interface with the Bittrex exchange
// </summary>
// ***********************************************************************
#pragma once

#include "db.h"
#include "api.h"
#include "bittrexapi.h"
#include "bittrexdatabase.h"
#include "interface.h"
#include "interfacehelper.h"

namespace trader {

    namespace BittrexApi {
        class EndPoints;
    };

    namespace BittrexDatabase {
        class Tables;
    };

    class Bittrex;

    class BittrexProcessingConnection : public Interface::MessageReceivingConnection
    {
    public:
        BittrexProcessingConnection()
        {

        }

        /// <summary>
        /// [Client-Side] Get a list of securities that can be traded on the exchange.
        /// </summary>
        /// <param name="securityListRequestData">Request Data</param>
        /// <param name="securityListRequestData.SecurityReqID">Unique identifier of this request.</param>
        void SecurityListRequest(Poco::AutoPtr<SecurityListRequestData> securityListRequestData) override;

        /// <summary>
        /// [Client-Side] Subscribes the current session to a Market Data - Snapshot/Full Refresh
        /// followed by zero or more Market Data - Incremental Refresh messages.
        /// </summary>
        /// <param name="marketDataRequestData">Market Data Request Params</param>
        /// <param name="marketDataRequestData.MDReqID">Unique identifier of the market data request.Uniqueness must be guaranteed by the institution for the duration of the connection to the market data channel.</param>
        /// <param name="marketDataRequestData.SubscriptionRequestType">Indicates what type of response is expected.
        ///              Valid Value: 1 = Snapshot + Updates(Subscribe)
        /// </param>
        /// <param name="marketDataRequestData.MarketDepth">Depth of the book to receive snapshot and updates for.</param>
        ///              Valid Value: 0 = Full Book, 1 = Top of Book
        /// </param>
        /// <param name="marketDataRequestData.NoMDEntryTypes">Number of MDEntryType fields requested</param>
        /// <param name="marketDataRequestData.MDEntryType">Type of market data entry to receive snapshots and updates for.</param>
        ///              Valid values : 0 = Bid
        ///                             1 = Offer
        ///                             2 = Trade
        ///                             Q = Auction Clearing Price
        /// </param>
        /// <param name="marketDataRequestData.NoRelatedSym">Number of symbols requested.</param>
        /// <param name="marketDataRequestData.Symbol">Market data symbol requested.
        ///                                            Valid Values : See Security List for a list of supported symbols.
        /// </param>
        void MarketDataRequest(Poco::AutoPtr<MarketDataRequestData> marketDataRequestData) override;

        /// <summary>
        /// [Client-Side] Submit a new order to exchange
        /// </summary>
        /// <param name="newOrderSingleData">New Order Single Data Params</param>
        /// <param name="newOrderSingleData.ClOrdID">Unique identifier of the order as assigned by the institution. Uniqueness must be guaranteed by the institution for the duration of the connection to the order entry channel.</param>
        /// <param name="newOrderSingleData.ExecInst">[Optional]Specifies that an order should be Maker-or-Cancel, TimeInForce must be 1 (Good Till Cancel)
        ///                                           Valid Value: 6 = Participate don't initiate (maker-or-cancel)
        /// </param>
        /// <param name="newOrderSingleData.OrderQty">Decimal amount of security to purchase. Full quantity will be visible on the book.</param>
        /// <param name="newOrderSingleData.OrdType">Order Type, Valid Value: 2 = Limit</param>
        /// <param name="newOrderSingleData.Price">[Optional]Decimal amount of USD to spend per Security.</param>
        ///                                        Price is required when OrdTyp is 2 = Limit.
        /// </param>
        /// <param name="newOrderSingleData.Side">Side of the order.
        ///                                       Valid Value: 1 = Buy, 2 = Sell
        /// </param>
        /// <param name="newOrderSingleData.Symbol">Market data symbol requested.
        ///                                         Valid Values : See Security List for a list of supported symbols.
        /// </param>
        /// <param name="newOrderSingleData.TimeInForce">Specifies how long the order remains in effect. Use 7 (At the close) for Auction orders
        ///                                              Valid Values : 1 = Good Till Cancel (GTC)
        ///                                                             3 = Immediate Or Cancel (IOC)
        /// </param>
        /// <param name="newOrderSingleData.TransactTime">Time of order creation(expressed in UTC).</param>
        void NewOrderSingle(Poco::AutoPtr<NewOrderSingleData> newOrderSingleData) override;

        // TODO: Documentation
        void OrderCancelRequest(Poco::AutoPtr<OrderCancelRequestData> orderCancelRequestData) override;

        // TODO: Documentation
        void TradeCaptureReportRequest(Poco::AutoPtr<TradeCaptureReportRequestData> tradeCaptureReportRequestData) override;

        void SetExchange(Bittrex* _exchange)
        {
            exchange = _exchange;
        }

        Bittrex* exchange;
    };

    class BittrexConnection : public Interface::CallConnection, public Poco::Runnable
    {
    public:
        BittrexConnection(const std::string& connectionid, Bittrex* _exchange)
            : processingConnection(10)
        {
            (void)connectionid;
            processingConnection.SetExchange(_exchange);
        }

        void ProcessMessage(Poco::AutoPtr<Interface::IMessageData> _messageData) override
        {
            processingConnection.ProcessMessage(_messageData);
        }

        void SetReceivingConnection(Poco::AutoPtr<Interface::Connection> _connection) override
        {
            processingConnection.SetReceivingConnection(_connection);
        }

        void run() override;

        void DoOperation(Poco::Int32 operation) override;

        BufferedConnection<BittrexProcessingConnection> processingConnection;
    };

    class Bittrex : public Api
    {
    public:
        Bittrex();

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
        
        static AutoPtr<Interface::Connection> getConnection(const std::string& connectionId);

    protected:
        Bittrex(const Bittrex&);
        Bittrex& operator = (const Bittrex&);

    };

}