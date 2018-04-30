#include "stdafx.h"

#include "traderapp.h"
#include "app.h"
#include "appconnection.h"
#include "connectionmanager.h"
#include "db.h"
#include "interface.h"
#include "marketdatasubsystem.h"

namespace trader
{

    int TraderApp::main(const std::vector< std::string > &args)
    {
        (void)args;
#if defined(__GNUC__)
        std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
        try
        {
            // Setup logs, proxy settings, db
            setup();

            // Add subsystems used by this application
            addSubsystem(new MarketDataSubSystem());

            //Create a new receiving connection
            setupAppConnection(this);

            //Load connection information from .properties file
            loadConnections();

            // Bootstrap user subsystems
            start();

            // Start Connections
            startConnections();

            //Start statechart
            AppStateChart::AppFSMList::start();

            // Run indefinitely
            do
            {
                Thread::sleep(10000);
            } while (1);
        }
        catch (Exception &exc)
        {
            cerr << exc.displayText() << std::endl;
            Logger::get("Logs").information("Application Error: %s", exc.displayText());
            poco_debugger();
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

    class GetMarketData;

    class WaitForMarketDataReady : public AppStateChart
    {

        void react(OnMarketDataReady const &) override
        {
            MarketDataSubSystem &marketDataSys =
                AppManager::instance.getApp()->getSubsystem< MarketDataSubSystem >();
            std::vector< std::string > markets;
            marketDataSys.retrieveMarkets(markets);
            for (auto &market : markets)
            {
                std::cout << market << std::endl;
            }

            transit< GetMarketData >();
        }
    };

    class GetMarketData : public AppStateChart
    {
        void entry() override
        {
            MarketDataSubSystem &marketDataSys =
                AppManager::instance.getApp()->getSubsystem< MarketDataSubSystem >();
            marketDataSys.requestMarketData("bittrex;config1_readonly:USDT-BTC");
        }

        void react(OnMarketUpdate const &) override {}
    };

} // namespace trader

FSM_INITIAL_STATE(trader::AppStateChart, trader::WaitForMarketDataReady);

POCO_APP_MAIN(trader::TraderApp)

// Sample Code

// trader::FybApi fyb(this);
// Poco::AutoPtr<trader::TickerDetailed> tickerDetailedData = fyb.GetTickerDetailed();
// std::cout << tickerDetailedData->ask << std::endl;
// Poco::AutoPtr<trader::OrderBook> orderBookData = fyb.GetOrderBook();
// std::cout << tickerDetailedData->ask << std::endl;
// Poco::AutoPtr<trader::TradesInput> tradesInputData = new trader::TradesInput();
// tradesInputData->object.since = 2095573;
// Poco::AutoPtr<trader::Trades> tradesData = fyb.GetTrades(tradesInputData);
// Poco::AutoPtr<trader::TimestampInput> timeStampInputData = new trader::TimestampInput();
// timeStampInputData->object.timestamp = std::time(nullptr);
// Poco::AutoPtr<trader::ErrorMessage> errorMsg = fyb.Test(timeStampInputData);
// Poco::AutoPtr<trader::AccountInfo> accountInfo = fyb.GetAccountInfo(timeStampInputData);
// Poco::AutoPtr<trader::PendingOrders> pendingOrders = fyb.GetPendingOrders();
// Poco::AutoPtr<trader::OrderHistoryParams> orderHistoryInputData = new trader::OrderHistoryParams();
// orderHistoryInputData->object.timestamp = std::time(nullptr);
// orderHistoryInputData->object.limit = 10;
// Poco::AutoPtr<trader::OrderHistory> orderHistory = fyb.GetOrderHistory(orderHistoryInputData);
// Poco::AutoPtr<trader::OrderParams> orderParams = new trader::OrderParams();
// orderParams->object.SetPrice(.1);
// orderParams->object.SetQty(.2);
// orderParams->object.SetTimestamp(std::time(nullptr));
// orderParams->object.SetType('B');
// Poco::AutoPtr<trader::OrderStatus> orderStatus = fyb.PlaceOrder(orderParams);
// Poco::AutoPtr<trader::CancelOrderParams> cancelOrderParams = new trader::CancelOrderParams();
// cancelOrderParams->object.SetOrderNo(2129260);
// cancelOrderParams->object.SetTimestamp(std::time(nullptr));
// Poco::AutoPtr<trader::ErrorNumber> errorNumber = fyb.CancelOrder(cancelOrderParams);
// trader::ExchangeratelabApi exchangeRateLab(this);
// Poco::AutoPtr<trader::SingleExchangeRate> singleExchangeRate = exchangeRateLab.GetUSDToSGD();

// Exchangeratelab exchangeRateLab(this);
// Fyb fyb(this);
// fyb.run();
// Poco::AutoPtr<trader::SingleExchangeRate> singleExchangeRate = exchangeRateLab.api.GetUSDToSGD();

// Cryptowatch cryptowatch(this);
// Poco::AutoPtr<AssetList> assetList = cryptowatch.api.GetAssetList();

// Kraken kraken(this);
// kraken.run();
// Poco::AutoPtr<AssetInfoParams> assetInfoParams = new AssetInfoParams();
// AutoPtr<AssetInfo> assetInfo = kraken.api.GetAssetInfo(assetInfoParams);

// AutoPtr<ServerTime> assetInfo = kraken.api.GetServerTime();

// AutoPtr<AccountBalance> accountBalance = kraken.api.GetAccountBalance();

// Poco::AutoPtr<AssetPairsParams> assetPairsParams = new AssetPairsParams();
// assetPairsParams->dataObject.pair = "XZECZUSD";
// AutoPtr<AssetPairs> assetPairs = kraken.api.GetAssetPairs(assetPairsParams);

// Poco::AutoPtr<TickerInformationParams> tickerInformationParams = new TickerInformationParams();
// tickerInformationParams->dataObject.pair = "XZECZUSD";
// AutoPtr<TickerInformation> tickerInformation = kraken.api.GetTickerInformation(tickerInformationParams);

// Poco::AutoPtr<KrakenApi::OHLCDataParams> ohlcDataParams = new KrakenApi::OHLCDataParams();
// ohlcDataParams->dataObject.pair = "XZECZUSD";
// AutoPtr<KrakenApi::OHLCData> ohlcData = kraken.api.GetOHLCData(ohlcDataParams);

// Poco::AutoPtr<KrakenApi::OrderBookParams> orderBookParams = new KrakenApi::OrderBookParams();
// orderBookParams->dataObject.pair = "XZECZUSD";
// AutoPtr<KrakenApi::OrderBook> orderBook = kraken.api.GetOrderBook(orderBookParams);

// Poco::AutoPtr<KrakenApi::RecentTradesParams> orderBookParams = new KrakenApi::RecentTradesParams();
// orderBookParams->dataObject.pair = "XZECZUSD";
// AutoPtr<KrakenApi::RecentTrades> orderBook = kraken.api.GetRecentTrades(orderBookParams);

// Poco::AutoPtr<KrakenApi::RecentSpreadParams> orderBookParams = new KrakenApi::RecentSpreadParams();
// orderBookParams->dataObject.pair = "XZECZUSD";
// AutoPtr<KrakenApi::RecentSpread> orderBook = kraken.api.GetRecentSpread(orderBookParams);

