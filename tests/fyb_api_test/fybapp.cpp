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
		Thread::sleep(1000);
		AutoPtr< TickerDetailed > tickerDetailedData;
		ASSERT_NO_THROW(tickerDetailedData = fyb->api.GetTickerDetailed());
		TickerDetailed::DataObject & item = tickerDetailedData->dataObject;
		EXPECT_TRUE(item.isSetAsk());
		EXPECT_TRUE(item.isSetBid());
		EXPECT_TRUE(item.isSetLast());
		EXPECT_TRUE(item.isSetVol());
    }

	TEST_F(FybTests, GetAccountInfo)
	{
		Thread::sleep(1000);
		AutoPtr< AccountInfo > accountInfo;
		ASSERT_NO_THROW(accountInfo = fyb->api.GetAccountInfo());
		AccountInfo::DataObject & item = accountInfo->dataObject;
		EXPECT_TRUE(item.isSetSgdBal());
		EXPECT_TRUE(item.isSetAccNo());
		EXPECT_TRUE(item.isSetBtcDeposit());
		EXPECT_TRUE(item.isSetEmail());
		EXPECT_TRUE(item.isSetBtcBal());
		EXPECT_TRUE(item.isSetError());
	}

	TEST_F(FybTests, GetTrades)
	{
		Thread::sleep(1000);
		AutoPtr< TradesParams> tradesParams = new TradesParams();
		tradesParams->dataObject.SetSince(2749925);
		AutoPtr< Trades > trades;
		ASSERT_NO_THROW(trades = fyb->api.GetTrades(tradesParams));
		for (auto &trade : trades->data)
		{
			EXPECT_TRUE(trade.isSetAmount());
			EXPECT_TRUE(trade.isSetDate());
			EXPECT_TRUE(trade.isSetPrice());
			EXPECT_TRUE(trade.isSetTid());
		}
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