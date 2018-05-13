#include "stdafx.h"
#include "app.h"
#include "db.h"
#include "applicationhelper.h"

namespace trader
{

    void ApplicationHelper::defineOptions(OptionSet &options)
    {
        Application::defineOptions(options);

        options.addOption(Option("help", "h", "Display help information on command line arguments.")
                              .required(false)
                              .repeatable(false)
                              .callback(OptionCallback< ApplicationHelper >(this, &ApplicationHelper::handleHelp)));
    }

    void ApplicationHelper::handleHelp(const string &name, const string &value)
    {
        (void)name;
        (void)value;
        displayHelp();
        stopOptionsProcessing();
    }

    void ApplicationHelper::displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A simple command line client for posting status updates.");
        helpFormatter.format(cout);
    }

    Poco::Util::AbstractConfiguration &ApplicationHelper::appConfig()
    {
        try
        {
            return Util::Application::instance().config();
        }
        catch (NullPointerException &)
        {
            throw IllegalStateException("An application configuration is required to initialize the application");
        }
    }

    void ApplicationHelper::setup()
    {
        // Initialize logs
        AutoPtr< SplitterChannel > splitterChannel(new SplitterChannel());
        ostringstream logNameStream;
        logNameStream << commandName() << ".log.txt";
#if defined(_DEBUG)
        AutoPtr< Channel > consoleChannel(new ConsoleChannel());
#endif
        AutoPtr< FileChannel > rotatedFileChannel(new FileChannel(logNameStream.str()));
        rotatedFileChannel->setProperty("archive", "timestamp");
        rotatedFileChannel->setProperty("rotateOnOpen", "true");
#if defined(_DEBUG)
        // splitterChannel->addChannel(consoleChannel);
#endif
        splitterChannel->addChannel(rotatedFileChannel);
        AutoPtr< Formatter > formatter(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
        AutoPtr< Channel > formattingChannel(new FormattingChannel(formatter, splitterChannel));
        Logger::create("Logs", formattingChannel, Message::PRIO_TRACE);

        // Loader application properties
        loadConfiguration();
        AutoPtr< AbstractConfiguration > proxyProperties(appConfig().createView("proxy"));

        // Grab proxy settings
        HTTPSClientSession::ProxyConfig proxyConfig;
        try
        {
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
        catch (Exception &exc)
        {
            Logger::get("Logs").information("Bad Application configuration: Missing or invalid %s.properties",
                                            commandName().c_str());
            Logger::get("Logs").information("Application Error: %s", exc.displayText());
        }
        HTTPSClientSession::setGlobalProxyConfig(proxyConfig);

        // Make application globally aware
        AppManager::instance.setApp(this);

        // Initialize DB
        ostringstream dbNameStream;

        dbNameStream << commandName() << ".db";
        DbManager::instance.setDb(new Db(new Data::Session("SQLite", dbNameStream.str())));
    }

	void ApplicationHelper::destroy()
	{
		Logger::destroy("Logs");
		DbManager::instance.setDb(nullptr);
        AppManager::instance.setApp(nullptr);
	}

    void ApplicationHelper::start() { this->initialize(*this); }

    bool ApplicationHelper::findFile(Path &path) const { return Util::Application::findFile(path); }

} // namespace trader
