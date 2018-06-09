#include "stdafx.h"

#include "sampleapp.h"
#include "app.h"
#include "db.h"
#include "interface.h"
#include "gtest/gtest.h"

static int savedArgc;
#if defined(_WIN32) && defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
static wchar_t **savedArgv;
#else
static char **savedArgv;
#endif

namespace trader
{

    class SampleAppTests : public ::testing::Test
    {
      protected:
        virtual void SetUp() {}

        virtual void TearDown() {}
    };

    TEST_F(SampleAppTests, InitApp)
    {
        Poco::AutoPtr< App > pApp = new trader::SampleApp;
        ASSERT_NO_THROW(pApp->init(savedArgc, savedArgv));
    }

    TEST_F(SampleAppTests, RunApp)
    {
        trader::SampleApp* pApp = new trader::SampleApp;
		ASSERT_NO_THROW(pApp->init(savedArgc, savedArgv));

        ASSERT_NO_THROW(pApp->run());
        ASSERT_NO_THROW(pApp->destroy());
    }

    TEST_F(SampleAppTests, SetupApp)
    {
        trader::SampleApp* pApp = new trader::SampleApp;
		ASSERT_NO_THROW(pApp->init(savedArgc, savedArgv));

        ASSERT_NO_THROW(pApp->setup());

        ASSERT_NO_THROW(pApp->destroy());
    }

    TEST_F(SampleAppTests, StartApp)
    {
        trader::SampleApp* pApp = new trader::SampleApp;
		ASSERT_NO_THROW(pApp->init(savedArgc, savedArgv));

		ASSERT_NO_THROW(pApp->setup());

        ASSERT_NO_THROW(pApp->start());

        ASSERT_NO_THROW(pApp->destroy());
    }

    int SampleApp::main(const std::vector< std::string > &args)
    {
		(void)args;
		setup();
		start();
        return Poco::Util::Application::EXIT_OK;
    }

} // namespace trader

#if defined(_WIN32) && defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
int wmain(int argc, wchar_t **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	savedArgc = argc;
	savedArgv = argv;
    return RUN_ALL_TESTS();
}
#else
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	savedArgc = argc;
	savedArgv = argv;
    return RUN_ALL_TESTS();
}
#endif
