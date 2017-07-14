#include "stdafx.h"
#include "fybapi.h"
#include "exchangeratelabapi.h"
#include "app.h"

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;
using Poco::Channel;
using Poco::ConsoleChannel;
using Poco::SplitterChannel;
using Poco::FileChannel;
using Poco::FormattingChannel;
using Poco::Formatter;
using Poco::PatternFormatter;
using Poco::Logger;
using Poco::Message;

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

    void App::handleHelp(const std::string& name, const std::string& value)
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
        helpFormatter.format(std::cout);
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
			std::ostringstream logNameStream;
			logNameStream << commandName() << ".log.txt";
			AutoPtr<Channel> consoleChannel(new ConsoleChannel());
			AutoPtr<FileChannel> rotatedFileChannel(new FileChannel(logNameStream.str()));

			rotatedFileChannel->setProperty("archive", "timestamp");
			rotatedFileChannel->setProperty("rotateOnOpen", "true");

			splitterChannel->addChannel(consoleChannel);
			splitterChannel->addChannel(rotatedFileChannel);

			AutoPtr<Formatter> formatter(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
			AutoPtr<Channel> formattingChannel(new FormattingChannel(formatter, splitterChannel));

			Logger::create("Logs", formattingChannel, Message::PRIO_TRACE);

			//Initialize DB
			std::ostringstream dbNameStream;
			dbNameStream << commandName() << ".db";
			dbSession = new Poco::Data::Session("SQLite", dbNameStream.str());

			trader::ExchangeratelabApi exchangeRateLab(this);
			trader::FybApi fyb(this);
			fyb.run();
			//Poco::AutoPtr<trader::SingleExchangeRate> singleExchangeRate = exchangeRateLab.GetUSDToSGD();

			do {
				Poco::Thread::sleep(10000);
			} while (1);
		}
        catch (Poco::Exception& exc)
        {
            std::cerr << exc.displayText() << std::endl;
			Poco::Logger::get("Logs").information("Application Error: %s", exc.displayText());
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

}

POCO_APP_MAIN(trader::App)
