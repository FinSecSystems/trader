#include "stdafx.h"

#include "fybapp.h"
#include "app.h"
#include "db.h"
#include "interface.h"
#include "dataconnector/fyb.h"
#include "gtest/gtest.h"

namespace trader
{
    using namespace trader::FybApi;

    class FybTests : public ::testing::Test
    {
    protected:
        virtual void SetUp() {
			gen = new std::mt19937(rd());
			fyb = new Fyb();
			fyb->setParams("config1_readonly");
        }

		virtual void TearDown() {
			delete fyb;
			delete gen;
		}

		Fyb* fyb;
		std::vector<string> marketNames;
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937* gen; //Standard mersenne_twister_engine seeded with rd()
    };

    TEST_F(FybTests, GetTickerDetailedData)
    {
		AutoPtr< TickerDetailed > tickerDetailedData;
		ASSERT_NO_THROW(tickerDetailedData = fyb->api.GetTickerDetailed());
		TickerDetailed::DataObject & item = tickerDetailedData->dataObject;
		EXPECT_TRUE(item.isSetAsk());
		EXPECT_TRUE(item.isSetBid());
		EXPECT_TRUE(item.isSetLast());
		EXPECT_TRUE(item.isSetVol());
    }
    
     int FybApp::main(const std::vector< std::string > &args)
    {
		(void)args;
		poco_bugcheck();
		return 0;
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
{
	::testing::InitGoogleTest(&argc, argv);
	trader::ApplicationHelper* pApp = new trader::FybApp;
	pApp->init(argc, argv);
	trader::setup(pApp);

	int res = RUN_ALL_TESTS();
	trader::destroy(pApp);
	return res;
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