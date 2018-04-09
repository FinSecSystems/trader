#pragma once

namespace trader
{

    class SampleConnection : public Interface::Connection
    {
      public:
        SampleConnection(const std::string &connectionid) { (void)connectionid; }

        /// <summary>
        /// [Client-Side] Get a list of securities that can be traded on the exchange.
        /// </summary>
        /// <param name="securityListRequestData">Request Data</param>
        /// <param name="securityListRequestData.SecurityReqID">Unique identifier of this request.</param>
        void SecurityListRequest(Poco::AutoPtr< SecurityListRequestData > securityListRequestData) override
        {
            // [Server-Side]
            // Returns a Security List Data of the of the securities traded on the exchange that match the criteria
            // provided. SecurityReqID - Unique identifier of the Security List Request <x> that solicited this
            // response. SecurityResponseID - Identifier for this message. TotNoRelatedSym- Number of securities
            // returned for the request. SecurityRequestResult - The result of this request.Valid values :
            //                                          0 = Valid Request, 2 = Invalid Request
            // NoRelatedSym - Specifies the number of returned securities.
            //                Symbol - Symbol of exchange - traded security.
            // Example:
            // Poco::AutoPtr<SecurityListData> securityListData = new SecurityListData();
            // receivingConnection->SecurityListRequest(securityListData);

            poco_bugcheck_msg("SecurityListRequest not implemented.");
        }

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
        void MarketDataRequest(Poco::AutoPtr< MarketDataRequestData > marketDataRequestData) override
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

            poco_bugcheck_msg("MarketDataRequest not implemented.");
        }

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
        void NewOrderSingle(Poco::AutoPtr< NewOrderSingleData > newOrderSingleData) override
        {
            // [Server-Side]
            // Returns  TradeCaptureReport and/or ExecutionReport
            // TODO: Documentation

            // Example:

            // Poco::AutoPtr<ExecutionReportData> executionReportData = new ExecutionReportData();
            // receivingConnection->ExecutionReport(executionReportData);

            poco_bugcheck_msg("NewOrderSingle not implemented.");
        }

        // TODO: Documentation
        void OrderCancelRequest(Poco::AutoPtr< OrderCancelRequestData > orderCancelRequestData) override
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

        // TODO: Documentation
        void
        TradeCaptureReportRequest(Poco::AutoPtr< TradeCaptureReportRequestData > tradeCaptureReportRequestData) override
        {
            // [Server-Side]
            // Returns TradeCaptureReport
            // TODO: Documentation

            // Example:
            // Poco::AutoPtr<TradeCaptureReportData> tradeCaptureReportData = new TradeCaptureReportData();
            // receivingConnection->TradeCaptureReport(TradeCaptureReportData);

            poco_bugcheck_msg("TradeCaptureReportRequest not implemented.");
        }
    };

} // namespace trader
