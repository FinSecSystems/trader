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
        }

        virtual void TearDown() {
            delete gen;
        }

        Bittrex bittrex;
        std::vector<string> marketNames;
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937* gen; //Standard mersenne_twister_engine seeded with rd()
    };

    TEST_F(BittrexTests, GetMarkets)
    {
        AutoPtr< BittrexApi::Markets > markets;
        ASSERT_NO_THROW(markets = bittrex.api.GetMarkets());
        for (auto item : markets->dataObject.result)
        {
            EXPECT_TRUE(item.isSetBaseCurrency());
            EXPECT_TRUE(item.isSetBaseCurrencyLong());
            EXPECT_TRUE(item.isSetCreated());
            EXPECT_TRUE(item.isSetIsActive());
            EXPECT_TRUE(item.isSetMarketCurrency());
            EXPECT_TRUE(item.isSetMarketCurrencyLong());
            EXPECT_TRUE(item.isSetMarketName());
            EXPECT_TRUE(item.isSetMinTradeSize());
            marketNames.push_back(item.marketName);
        }
    }
    
    TEST_F(BittrexTests, GetBalance)
    {
        AutoPtr< BittrexApi::BalanceParams > balanceParam = new BittrexApi::BalanceParams();
        balanceParam->dataObject.SetCurrency("BTC");
        AutoPtr< BittrexApi::Balance > balance;
        ASSERT_NO_THROW(balance = bittrex.api.GetBalance(balanceParam));
        for (auto item : balance->dataObject.result)
        {
            EXPECT_TRUE(item.isSetAvailable());
            EXPECT_TRUE(item.isSetBalance());
            EXPECT_TRUE(item.isSetCryptoAddress());
            EXPECT_TRUE(item.isSetCurrency());
            EXPECT_TRUE(item.isSetPending());
            EXPECT_TRUE(item.isSetRequested());
            EXPECT_TRUE(item.isSetUuid());
        }
    }

    TEST_F(BittrexTests, GetMarketHistory)
    {
        AutoPtr< BittrexApi::HistoryParams > historyParam = new BittrexApi::HistoryParams();
        std::uniform_int_distribution<> dis(0, (int) marketNames.size()-1);
        historyParam->dataObject.SetMarket(marketNames[dis(*gen)]);
        AutoPtr< BittrexApi::History > history;
        ASSERT_NO_THROW(history = bittrex.api.GetMarketHistory(historyParam));
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

    int BittrexApp::main(const std::vector< std::string > &args)
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
            return Application::EXIT_SOFTWARE;
        }

        int argc = (int) args.size();
        char** argv = new char*[args.size()];
        for (UInt32 count = 0; count < args.size(); count++)
        {
            argv[count] = (char*) args[count].c_str();
        }

        ::testing::InitGoogleTest(&argc, argv);
        delete[] argv;
        return RUN_ALL_TESTS();
    }

} // namespace trader

POCO_APP_MAIN(trader::BittrexApp)
