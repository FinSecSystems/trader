#include "stdafx.h"

#include "bittrexapp.h"
#include "app.h"
#include "db.h"
#include "interface.h"
#include "dataconnector/bittrex.h"
#include "gtest/gtest.h"

namespace trader
{
    using namespace trader::BittrexApi;

    class BittrexTests : public ::testing::Test
    {
    protected:
        virtual void SetUp() {
			gen = new std::mt19937(rd());
			bittrex = new Bittrex();
            bittrex->setParams("config1_readonly");
        }

		virtual void TearDown() {
			delete bittrex;
			delete gen;
		}

		Bittrex* bittrex;
		std::vector<string> marketNames;
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937* gen; //Standard mersenne_twister_engine seeded with rd()
    };

    TEST_F(BittrexTests, GetMarkets)
    {
        AutoPtr< BittrexApi::Markets > markets;
        ASSERT_NO_THROW(markets = bittrex->api.GetMarkets());
        for (auto item : markets->dataObject.result)
        {
            EXPECT_TRUE(item.isSetBaseCurrency());
            EXPECT_TRUE(item.isSetBaseCurrencyLong());
            EXPECT_TRUE(item.isSetIsActive());
            EXPECT_GT(item.created.time, 0);
            EXPECT_TRUE(item.isSetMarketCurrency());
            EXPECT_TRUE(item.isSetMarketCurrencyLong());
            EXPECT_TRUE(item.isSetMarketName());
            EXPECT_TRUE(item.isSetMinTradeSize());
        }
    }
    
    TEST_F(BittrexTests, GetBalance)
    {
        AutoPtr< BittrexApi::BalanceParams > balanceParam = new BittrexApi::BalanceParams();
        balanceParam->dataObject.SetCurrency("BTC");
        AutoPtr< BittrexApi::Balance > balance;
        ASSERT_NO_THROW(balance = bittrex->api.GetBalance(balanceParam));
        for (auto item : balance->dataObject.result)
        {
            EXPECT_TRUE(item.isSetAvailable());
            EXPECT_TRUE(item.isSetBalance());
            //EXPECT_TRUE(item.isSetCryptoAddress());
            EXPECT_TRUE(item.isSetCurrency());
            EXPECT_TRUE(item.isSetPending());
            //EXPECT_TRUE(item.isSetRequested());
            //EXPECT_TRUE(item.isSetUuid());
        }
    }

    TEST_F(BittrexTests, GetMarketHistory)
    {
		AutoPtr< BittrexApi::Markets > markets;
		ASSERT_NO_THROW(markets = bittrex->api.GetMarkets());
		for (auto item : markets->dataObject.result)
		{
			marketNames.push_back(item.marketName);
		}

        AutoPtr< BittrexApi::HistoryParams > historyParam = new BittrexApi::HistoryParams();
        std::uniform_int_distribution<> dis(0, (int) marketNames.size()-1);
        historyParam->dataObject.SetMarket(marketNames[dis(*gen)]);
        AutoPtr< BittrexApi::History > history;
        ASSERT_NO_THROW(history = bittrex->api.GetMarketHistory(historyParam));
        for (auto item : history->dataObject.result)
        {
            EXPECT_TRUE(item.isSetFillType());
            EXPECT_TRUE(item.isSetId());
            EXPECT_TRUE(item.isSetOrderType());
            EXPECT_TRUE(item.isSetPrice());
            EXPECT_TRUE(item.isSetQuantity());
            EXPECT_TRUE(item.isSetTotal());
        }
    }

    TEST_F(BittrexTests, GetOrderBook)
    {
        AutoPtr< BittrexApi::Markets > markets;
        ASSERT_NO_THROW(markets = bittrex->api.GetMarkets());
        for (auto item : markets->dataObject.result)
        {
            marketNames.push_back(item.marketName);
        }

        AutoPtr< BittrexApi::OrderBookParams > orderBookParam = new BittrexApi::OrderBookParams();
        std::uniform_int_distribution<> dis(0, (int)marketNames.size() - 1);
        orderBookParam->dataObject.SetMarket(marketNames[dis(*gen)]);
        orderBookParam->dataObject.SetType("buy");
        AutoPtr< BittrexApi::OrderBook > orderBookBuy;
        ASSERT_NO_THROW(orderBookBuy = bittrex->api.GetOrderBook(orderBookParam));
        for (auto item : orderBookBuy->dataObject.result)
        {
            EXPECT_TRUE(item.isSetQuantity());
            EXPECT_TRUE(item.isSetRate());
        }

        orderBookParam->dataObject.SetType("sell");
        AutoPtr< BittrexApi::OrderBook > orderBookSell;
        ASSERT_NO_THROW(orderBookSell = bittrex->api.GetOrderBook(orderBookParam));
        for (auto item : orderBookSell->dataObject.result)
        {
            EXPECT_TRUE(item.isSetQuantity());
            EXPECT_TRUE(item.isSetRate());
        }

        orderBookParam->dataObject.SetType("both");
        AutoPtr< BittrexApi::OrderBookBoth > orderBookBoth;
        ASSERT_NO_THROW(orderBookBoth = bittrex->api.GetBothOrderBooks(orderBookParam));
        for (auto item : orderBookBoth->dataObject.resultObject.sell)
        {
            EXPECT_TRUE(item.isSetQuantity());
            EXPECT_TRUE(item.isSetRate());
        }
        for (auto item : orderBookBoth->dataObject.resultObject.buy)
        {
            EXPECT_TRUE(item.isSetQuantity());
            EXPECT_TRUE(item.isSetRate());
        }
    }

    int BittrexApp::main(const std::vector< std::string > &args)
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
	trader::ApplicationHelper* pApp = new trader::BittrexApp;
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