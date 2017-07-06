#include "stdafx.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "fyb.h"
#include "fybconfig.h"
#include <iostream>
#include <iomanip>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;


class TraderApp : public Application
{
public:
    TraderApp()
    {
    }

protected:
    void defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h", "Display help information on command line arguments.")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleHelp)));

        options.addOption(
            Option("message", "m", "Specify the status message to post.")
            .required(false)
            .repeatable(false)
            .argument("message")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleMessage)));

        options.addOption(
            Option("consumer_key", "c", "Specify the consumer key.")
            .required(false)
            .repeatable(false)
            .argument("consumer key")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleConsumerKey)));

        options.addOption(
            Option("consumer_secret", "s", "Specify the consumer secret.")
            .required(false)
            .repeatable(false)
            .argument("consumer secret")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleConsumerSecret)));

        options.addOption(
            Option("token", "t", "Specify the access token.")
            .required(false)
            .repeatable(true)
            .argument("access token")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleAccessToken)));

        options.addOption(
            Option("token_secret", "S", "Specify the access token secret.")
            .required(false)
            .repeatable(true)
            .argument("access token secret")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleAccessTokenSecret)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
		(void)name;
		(void)value;
        displayHelp();
        stopOptionsProcessing();
    }

    void handleConsumerKey(const std::string& name, const std::string& value)
    {
		(void)name;
		_consumerKey = value;
    }

    void handleConsumerSecret(const std::string& name, const std::string& value)
    {
		(void)name;
        _consumerSecret = value;
    }

    void handleAccessToken(const std::string& name, const std::string& value)
    {
		(void)name;
		_accessToken = value;
    }

    void handleAccessTokenSecret(const std::string& name, const std::string& value)
    {
		(void)name;
		_accessTokenSecret = value;
    }

    void handleMessage(const std::string& name, const std::string& value)
    {
		(void)name;
		_message = value;
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A simple command line client for posting status updates.");
        helpFormatter.format(std::cout);
    }

    int main(const std::vector<std::string>& args)
    {
		(void)args;
        try
        {
			Poco::Path fybConfigFileName("fyb.config.json");
			if (findFile(fybConfigFileName))
			{
				Poco::AutoPtr<trader::fybconfig> fybConfig = new trader::fybconfig();
				fybConfig->readFile(fybConfigFileName.toString());
				if (_consumerKey.empty())
				{
					_consumerKey = fybConfig->object.consumer_key;
				}
				if (_consumerSecret.empty())
				{
					_consumerSecret = fybConfig->object.consumer_secret;
				}
			}
            trader::fyb fyb;
            fyb.login(_consumerKey, _consumerSecret, _accessToken, _accessTokenSecret);
            //Poco::AutoPtr<trader::TickerDetailed> tickerDetailedData = fyb.GetTickerDetailed();
            //std::cout << tickerDetailedData->ask << std::endl;
			//Poco::AutoPtr<trader::OrderBook> orderBookData = fyb.GetOrderBook();
			//std::cout << tickerDetailedData->ask << std::endl;
			//Poco::AutoPtr<trader::TradesInput> tradesInputData = new trader::TradesInput();
			//tradesInputData->object.since = 2095573;
			//Poco::AutoPtr<trader::Trades> tradesData = fyb.GetTrades(tradesInputData);
			Poco::AutoPtr<trader::TimestampInput> timeStampInputData = new trader::TimestampInput();
			timeStampInputData->object.timestamp = std::time(nullptr);
			Poco::AutoPtr<trader::ErrorMessage> errorMsg = fyb.Test(timeStampInputData);
		}
        catch (Poco::Exception& exc)
        {
            std::cerr << exc.displayText() << std::endl;
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

private:
    std::string _consumerKey;
    std::string _consumerSecret;
    std::string _accessToken;
    std::string _accessTokenSecret;
    std::string _message;
};


POCO_APP_MAIN(TraderApp)
