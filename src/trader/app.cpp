#include "stdafx.h"
#include "fyb.h"
#include "exchangeratelab.h"
#include "app.h"
#include "cryptowatch.h"
#include "kraken.h"
#include "bittrex.h"

namespace trader {

    void App::defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h", "Display help information on command line arguments.")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<App>(this, &App::handleHelp)));

    }

    void App::handleHelp(const string& name, const string& value)
    {
		(void)name;
		(void)value;
        displayHelp();
        stopOptionsProcessing();
    }

     void App::displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A simple command line client for posting status updates.");
        helpFormatter.format(cout);
    }

     Poco::Util::AbstractConfiguration& App::appConfig()
     {
         try
         {
             return Util::Application::instance().config();
         }
         catch (NullPointerException&)
         {
             throw IllegalStateException(
                 "An application configuration is required to initialize the application"
             );
         }
     }

    int App::main(const std::vector<std::string>& args)
    {
		(void)args;
        try
        {
            //trader::FybApi fyb(this);
            //Poco::AutoPtr<trader::TickerDetailed> tickerDetailedData = fyb.GetTickerDetailed();
            //std::cout << tickerDetailedData->ask << std::endl;
			//Poco::AutoPtr<trader::OrderBook> orderBookData = fyb.GetOrderBook();
			//std::cout << tickerDetailedData->ask << std::endl;
			//Poco::AutoPtr<trader::TradesInput> tradesInputData = new trader::TradesInput();
			//tradesInputData->object.since = 2095573;
			//Poco::AutoPtr<trader::Trades> tradesData = fyb.GetTrades(tradesInputData);
			//Poco::AutoPtr<trader::TimestampInput> timeStampInputData = new trader::TimestampInput();
			//timeStampInputData->object.timestamp = std::time(nullptr);
			//Poco::AutoPtr<trader::ErrorMessage> errorMsg = fyb.Test(timeStampInputData);
			//Poco::AutoPtr<trader::AccountInfo> accountInfo = fyb.GetAccountInfo(timeStampInputData);
			//Poco::AutoPtr<trader::PendingOrders> pendingOrders = fyb.GetPendingOrders();
			//Poco::AutoPtr<trader::OrderHistoryParams> orderHistoryInputData = new trader::OrderHistoryParams();
			//orderHistoryInputData->object.timestamp = std::time(nullptr);
			//orderHistoryInputData->object.limit = 10;
			//Poco::AutoPtr<trader::OrderHistory> orderHistory = fyb.GetOrderHistory(orderHistoryInputData);
			//Poco::AutoPtr<trader::OrderParams> orderParams = new trader::OrderParams();
			//orderParams->object.SetPrice(.1);
			//orderParams->object.SetQty(.2);
			//orderParams->object.SetTimestamp(std::time(nullptr));
			//orderParams->object.SetType('B');
			//Poco::AutoPtr<trader::OrderStatus> orderStatus = fyb.PlaceOrder(orderParams);
			//Poco::AutoPtr<trader::CancelOrderParams> cancelOrderParams = new trader::CancelOrderParams();
			//cancelOrderParams->object.SetOrderNo(2129260);
			//cancelOrderParams->object.SetTimestamp(std::time(nullptr));
			//Poco::AutoPtr<trader::ErrorNumber> errorNumber = fyb.CancelOrder(cancelOrderParams);
			//trader::ExchangeratelabApi exchangeRateLab(this);
			//Poco::AutoPtr<trader::SingleExchangeRate> singleExchangeRate = exchangeRateLab.GetUSDToSGD();

			//Initialize logs
			AutoPtr<SplitterChannel> splitterChannel(new SplitterChannel());
			ostringstream logNameStream;
			logNameStream << commandName() << ".log.txt";
#if defined(_DEBUG)
			AutoPtr<Channel> consoleChannel(new ConsoleChannel());
#endif
			AutoPtr<FileChannel> rotatedFileChannel(new FileChannel(logNameStream.str()));

			rotatedFileChannel->setProperty("archive", "timestamp");
			rotatedFileChannel->setProperty("rotateOnOpen", "true");

#if defined(_DEBUG)
			//splitterChannel->addChannel(consoleChannel);
#endif
			splitterChannel->addChannel(rotatedFileChannel);

			AutoPtr<Formatter> formatter(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
			AutoPtr<Channel> formattingChannel(new FormattingChannel(formatter, splitterChannel));

			Logger::create("Logs", formattingChannel, Message::PRIO_TRACE);

			//Initialize DB
			ostringstream dbNameStream;
			dbNameStream << commandName() << ".db";
			dbSession = new Data::Session("SQLite", dbNameStream.str());

            loadConfiguration();
            AutoPtr<AbstractConfiguration> proxyProperties(appConfig().createView("proxy"));

            HTTPSClientSession::ProxyConfig proxyConfig;
			if (proxyProperties->hasProperty("hostname"))
				proxyConfig.host = proxyProperties->getString("hostname");
			if (proxyProperties->hasProperty("port"))
				proxyConfig.port = (UInt16)proxyProperties->getUInt("port");
			if (proxyProperties->hasProperty("username"))
				proxyConfig.username = proxyProperties->getString("username");
			if (proxyProperties->hasProperty("password"))
				proxyConfig.password = proxyProperties->getString("password");
			if (proxyProperties->hasProperty("nonproxyhosts"))
				proxyConfig.nonProxyHosts = proxyProperties->getString("nonproxyhosts");

            HTTPSClientSession::setGlobalProxyConfig(proxyConfig);

			Exchangeratelab exchangeRateLab(this);
			Fyb fyb(this);
			//fyb.run();
			//Poco::AutoPtr<trader::SingleExchangeRate> singleExchangeRate = exchangeRateLab.api.GetUSDToSGD();

            Cryptowatch cryptowatch(this);
            //Poco::AutoPtr<AssetList> assetList = cryptowatch.api.GetAssetList();

            Kraken kraken(this);
            //kraken.run();
            //Poco::AutoPtr<AssetInfoParams> assetInfoParams = new AssetInfoParams();
            //AutoPtr<AssetInfo> assetInfo = kraken.api.GetAssetInfo(assetInfoParams);

            //AutoPtr<ServerTime> assetInfo = kraken.api.GetServerTime();

            //AutoPtr<AccountBalance> accountBalance = kraken.api.GetAccountBalance();

            //Poco::AutoPtr<AssetPairsParams> assetPairsParams = new AssetPairsParams();
            //assetPairsParams->dataObject.pair = "XZECZUSD";
            //AutoPtr<AssetPairs> assetPairs = kraken.api.GetAssetPairs(assetPairsParams);

            //Poco::AutoPtr<TickerInformationParams> tickerInformationParams = new TickerInformationParams();
            //tickerInformationParams->dataObject.pair = "XZECZUSD";
            //AutoPtr<TickerInformation> tickerInformation = kraken.api.GetTickerInformation(tickerInformationParams);

            //Poco::AutoPtr<KrakenApi::OHLCDataParams> ohlcDataParams = new KrakenApi::OHLCDataParams();
            //ohlcDataParams->dataObject.pair = "XZECZUSD";
            //AutoPtr<KrakenApi::OHLCData> ohlcData = kraken.api.GetOHLCData(ohlcDataParams);

            //Poco::AutoPtr<KrakenApi::OrderBookParams> orderBookParams = new KrakenApi::OrderBookParams();
            //orderBookParams->dataObject.pair = "XZECZUSD";
            //AutoPtr<KrakenApi::OrderBook> orderBook = kraken.api.GetOrderBook(orderBookParams);

            //Poco::AutoPtr<KrakenApi::RecentTradesParams> orderBookParams = new KrakenApi::RecentTradesParams();
            //orderBookParams->dataObject.pair = "XZECZUSD";
            //AutoPtr<KrakenApi::RecentTrades> orderBook = kraken.api.GetRecentTrades(orderBookParams);

            //Poco::AutoPtr<KrakenApi::RecentSpreadParams> orderBookParams = new KrakenApi::RecentSpreadParams();
            //orderBookParams->dataObject.pair = "XZECZUSD";
            //AutoPtr<KrakenApi::RecentSpread> orderBook = kraken.api.GetRecentSpread(orderBookParams);

            Bittrex bittrex(this);
            while (1)
            {
                bittrex.run();
                break;
            }
            //AutoPtr<BittrexApi::Markets> markets = bittrex.api.GetMarkets();

			AutoPtr<BittrexApi::BalanceParams> balanceParam = new BittrexApi::BalanceParams();
			balanceParam->dataObject.SetCurrency("BTC");
			AutoPtr<BittrexApi::Balance> balance = bittrex.api.GetBalance(balanceParam);

			do {
				Thread::sleep(10000);
			} while (1);
		}
        catch (Exception& exc)
        {
            cerr << exc.displayText() << std::endl;
			Logger::get("Logs").information("Application Error: %s", exc.displayText());
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

	bool App::findFile(Path& path) const
	{
		return Util::Application::findFile(path);
	}

}

POCO_APP_MAIN(trader::App) 
