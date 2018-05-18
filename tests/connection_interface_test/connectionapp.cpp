#include "stdafx.h"

#include "connectionapp.h"
#include "app.h"
#include "db.h"
#include "interface.h"
#include "gtest/gtest.h"
#include "connectionmanager.h"

namespace trader
{

    class ConnectionTests : public ::testing::Test
    {
    protected:
        virtual void SetUp() {
        }

		virtual void TearDown() {
		}

    };

    TEST_F(ConnectionTests, StartSingleConnection)
    {
        // Retrieve required connections from Connection Manager
        std::vector< std::string > connectionStrings;
        connectionStrings.push_back("bittrex");

        AutoPtr<trader::ConnectionApp> pApp = trader::AppManager::instance.getApp().unsafeCast<trader::ConnectionApp>();
        ASSERT_NO_THROW(pApp->setupConnections(connectionStrings));

        // Start Connections
        ASSERT_NO_THROW(pApp->startConnections());

        AutoPtr< trader::Interface::Connection > connection = ConnectionManager::instance.get()->getConnection("bittrex");
        EXPECT_NE(connection.get(), nullptr);

		// Stop Connections
		ASSERT_NO_THROW(pApp->stopConnections());

    }
    
    int ConnectionApp::main(const std::vector< std::string > &args)
    {
        (void)args;
#if defined(__GNUC__)
        std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
        try
        {
            // Setup logs, proxy settings, db
            setup();

            // Bootstrap subsystems
            start();

        }
        catch (Exception &exc)
        {
            cerr << exc.displayText() << std::endl;
            Logger::get("Logs").information("Application Error: %s", exc.displayText());
            poco_debugger();
       }
		return Application::EXIT_SOFTWARE;
	}

	void setup(trader::ApplicationHelper* pApp)
	{
		pApp->setup();
		pApp->start();
	}

	void destroy(trader::ApplicationHelper* pApp)
	{
		pApp->destroy();
	}

} // namespace trader

#if defined(_WIN32) && defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
int wmain(int argc, wchar_t **argv)
#else
int main(int argc, char **argv)
#endif
{
	::testing::InitGoogleTest(&argc, argv);
	Poco::AutoPtr<trader::ApplicationHelper> pApp = new trader::ConnectionApp;
	pApp->init(argc, argv);
	trader::setup(pApp);

	int res = RUN_ALL_TESTS();
	trader::destroy(pApp);
	return res;
}
