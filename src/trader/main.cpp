#include "stdafx.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "fyb.h"
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
            Option("ckey", "c", "Specify the consumer key.")
            .required(false)
            .repeatable(false)
            .argument("consumer key")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleConsumerKey)));

        options.addOption(
            Option("csecret", "s", "Specify the consumer secret.")
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
            Option("tsecret", "S", "Specify the access token secret.")
            .required(false)
            .repeatable(true)
            .argument("access token secret")
            .callback(OptionCallback<TraderApp>(this, &TraderApp::handleAccessTokenSecret)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        displayHelp();
        stopOptionsProcessing();
    }

    void handleConsumerKey(const std::string& name, const std::string& value)
    {
        _consumerKey = value;
    }

    void handleConsumerSecret(const std::string& name, const std::string& value)
    {
        _consumerSecret = value;
    }

    void handleAccessToken(const std::string& name, const std::string& value)
    {
        _accessToken = value;
    }

    void handleAccessTokenSecret(const std::string& name, const std::string& value)
    {
        _accessTokenSecret = value;
    }

    void handleMessage(const std::string& name, const std::string& value)
    {
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
        try
        {
           // if (!_message.empty())
            {
                /*
                Poco::Path filePath("config.json");

                std::ostringstream ostr;

                if (filePath.isFile())
                {
                    Poco::File inputFile(filePath);
                    if (inputFile.exists())
                    {
                        Poco::FileInputStream fis(filePath.toString());
                        Poco::StreamCopier::copyStream(fis, ostr);
                    }
                    else
                    {
                        std::cout << filePath.toString() << " doesn't exist!" << std::endl;
                        return 1;
                    }
                }

                std::string jsonStr = ostr.str();
                Poco::JSON::Parser sparser(0);
                sparser.parse(jsonStr);
                Poco::DynamicAny result = sparser.result();
                */



                Fyb fyb;
                fyb.login(_consumerKey, _consumerSecret, _accessToken, _accessTokenSecret);
                double ask = fyb.tickerdetailed();
                std::cout << ask << std::endl;
            }
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
