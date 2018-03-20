#include "stdafx.h"
#include "db.h"
#include "app.h"
#include "connectionmanager.h"
#include "traderapp.h"
#include "interface.h"
#include "appconnection.h"
#include "marketdatasubsystem.h"

namespace trader {

    void TraderApp::defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h", "Display help information on command line arguments.")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleHelp)));

    }

    void TraderApp::handleHelp(const string& name, const string& value)
    {
		(void)name;
		(void)value;
        displayHelp();
        stopOptionsProcessing();
    }

     void TraderApp::displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A simple command line client for posting status updates.");
        helpFormatter.format(cout);
    }

     Poco::Util::AbstractConfiguration& TraderApp::appConfig()
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

    int TraderApp::main(const std::vector<std::string>& args)
    {
		(void)args;
#if defined(__GNUC__)
        std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
        try
        {
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

            // Loader application properties
            loadConfiguration();
            AutoPtr<AbstractConfiguration> proxyProperties(appConfig().createView("proxy"));

            // Grab proxy settings
            HTTPSClientSession::ProxyConfig proxyConfig;
            try {
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
            }
            catch (Exception& exc)
            {
                Logger::get("Logs").information("Bad Application configuration: Missing or invalid %s.properties", commandName().c_str());
                Logger::get("Logs").information("Application Error: %s", exc.displayText());
            }
            HTTPSClientSession::setGlobalProxyConfig(proxyConfig);

            //Make application globally aware
            AppManager::instance.get()->setApp(this);

            //Initialize DB
            ostringstream dbNameStream;
            dbNameStream << commandName() << ".db";
            DbManager::instance.setDb(new Db(new Data::Session("SQLite", dbNameStream.str())));

            //Add Subsystems used by this application
            addSubsystem(new MarketDataSubSystem());
            
            //Retrieve required connections from Connection Manager
            connections.push_back(ConnectionManager::instance.get()->getConnection("bittrex"));
            
            //Setup connection for this applicatino to receive messages
            appConnection = new AppConnection(this);
            for (auto& connection : connections)
            {
                connection->SetReceivingConnection(appConnection);
            }

            //Bootstrap subsystems
            this->initialize(*this);
            ConnectionManager::instance.get()->DoOperation(DC_START);

            //Run indefinitely
			do {
				Thread::sleep(10000);
			} while (1); 
		}
        catch (Exception& exc)
        {
            cerr << exc.displayText() << std::endl;
			Logger::get("Logs").information("Application Error: %s", exc.displayText());
            poco_debugger();
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

	bool TraderApp::findFile(Path& path) const
	{
		return Util::Application::findFile(path);
	}

}

POCO_APP_MAIN(trader::TraderApp)


//Sample Code

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

//Exchangeratelab exchangeRateLab(this);
//Fyb fyb(this);
//fyb.run();
//Poco::AutoPtr<trader::SingleExchangeRate> singleExchangeRate = exchangeRateLab.api.GetUSDToSGD();

//Cryptowatch cryptowatch(this);
//Poco::AutoPtr<AssetList> assetList = cryptowatch.api.GetAssetList();

//Kraken kraken(this);
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

//Bittrex bittrex(this);
//while (1)
//{
//    bittrex.run();
//    break;
//}
//AutoPtr<BittrexApi::Markets> markets = bittrex.api.GetMarkets();

//AutoPtr<BittrexApi::BalanceParams> balanceParam = new BittrexApi::BalanceParams();
//balanceParam->dataObject.SetCurrency("BTC");
//AutoPtr<BittrexApi::Balance> balance = bittrex.api.GetBalance(balanceParam);