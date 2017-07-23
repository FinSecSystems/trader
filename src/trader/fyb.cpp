#include "stdafx.h"
#include "fyb.h"
#include "fybapi.h"
#include "fybconfig.h"
#include "fybdatabase.h"
#include "helper.h"

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;
using Poco::Data::TypeHandler;
using Poco::Data::AbstractBinder;
using Poco::Data::AbstractExtractor;
using Poco::Data::AbstractPreparator;
using Poco::AutoPtr;
using namespace std;
using namespace Poco;

namespace trader {

	Fyb::Fyb()
		: fybApi(*((FybApi*)this))
		, executeTickerDetailedTimer(0, 6006)
		, executeAccountInfoTimer(1001, 6006)
		, executeTradeHistoryTimer(2002, 6006)
		, executeOrderBookTimer(3003, 6006)
		, executePendingOrderTimer(4004, 6006)
		, executeOrderHistoryTimer(5005, 6006)
	{
	}

	void Fyb::run()
	{
		db = fybApi._app->dbSession;

		dataBase = new FybDatabase(db);
		dataBase->init();
		dataBase->clear();
	
		//executeTickerDetailedTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeTickerDetailed));
		//executeAccountInfoTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeAccountInfo));
		//executeTradeHistoryTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeTradeHistory));
		executeOrderBookTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeOrderBook));
		//executePendingOrderTimer.start(TimerCallback<Fyb>(*this, &Fyb::executePendingOrders));
		//executeOrderHistoryTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeOrderHistory));
	}

	void Fyb::executeTickerDetailed(Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<TickerDetailed> tickerDetailedData = fybApi.GetTickerDetailed();

		Ticker_Detailed::Record rec;
		rec.timeStamp = (Poco::Int32)std::time(nullptr);
		rec.ask = tickerDetailedData->dataObject.ask;
		rec.bid = tickerDetailedData->dataObject.bid;
		rec.last = tickerDetailedData->dataObject.last;
		rec.vol = tickerDetailedData->dataObject.vol;

		dataBase->ticker_DetailedTable->insertAndDeleteUnchanged(rec);
	}

	void Fyb::executeAccountInfo(Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<AccountInfo> accountInfo = fybApi.GetAccountInfo();
		
		Account_Balance::Record rec;
		rec.timeStamp = (Poco::Int32)std::time(nullptr);
		rec.sgdBal = accountInfo->dataObject.sgdBal;
		rec.btcBal = accountInfo->dataObject.btcBal;

		dataBase->account_BalanceTable->insertAndDeleteUnchanged(rec);

		std::ostringstream accountInfoStream;
		accountInfoStream << "FYB" << accountInfo->dataObject.accNo;
		Statement insertAccountInfo(*db);

		Account_Info::Record recInfo;
		recInfo.accNum = accountInfoStream.str();
		recInfo.btcAddress = accountInfo->dataObject.btcDeposit;
		recInfo.email = accountInfo->dataObject.email;

		dataBase->account_InfoTable->insertOnce(recInfo);
	}

	void Fyb::executeTradeHistory(Timer& timer)
	{
		(void)timer;

		Trade_History::Record currentRec;
		dataBase->trade_HistoryTable->getLatest(currentRec);

		AutoPtr<TradesParams> tradesParams = new TradesParams();
		if (currentRec.isSetTid())
		{
			tradesParams->dataObject.SetSince(currentRec.tid);
		}

		AutoPtr<Trades> trades = fybApi.GetTrades(tradesParams);

		std::vector<Trade_History::Record> tradeHistoryRecord;
		for (auto& trade : trades->data)
		{
			Trade_History::Record rec;
			rec.amt = trade.amount;
			rec.date = (Poco::Int32)trade.date;
			rec.price = trade.price;
			rec.tid = trade.tid;
			tradeHistoryRecord.push_back(rec);
		}
		dataBase->trade_HistoryTable->insertMultipleUnique(tradeHistoryRecord);
	}

	void Fyb::executeOrderBook(Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<OrderBook> orderBook = fybApi.GetOrderBook();
		time_t currentDateTime = std::time(nullptr);

		if (orderBook->dataObject.asks.empty())
			return;

		Order_Book_Asks::Record latestAsk;
		dataBase->order_Book_AsksTable->getLatest(latestAsk);
		if (!latestAsk.isSetPrice()
			|| !latestAsk.isSetVolume()
			|| !equal<double>(orderBook->dataObject.asks[0][0], latestAsk.price)
			|| !equal<double>(orderBook->dataObject.asks[0][1], latestAsk.volume))
		{
			std::vector<Order_Book_Asks::Record> askRecords;
			for (auto& ask : orderBook->dataObject.asks)
			{
				Order_Book_Asks::Record askRecord;
				askRecord.price = ask[0];
				askRecord.volume = ask[1];
				askRecords.push_back(askRecord);
			}
			dataBase->order_Book_AsksTable->clear();
			dataBase->order_Book_AsksTable->insertMultiple(askRecords);
		}

		if (orderBook->dataObject.bids.empty())
			return;

		Order_Book_Bids::Record latestBid;
		dataBase->order_Book_BidsTable->getLatest(latestBid);
		if (!latestBid.isSetPrice() 
			|| !latestBid.isSetVolume()
			|| !equal<double>(orderBook->dataObject.bids[0][0], latestBid.price)
			|| !equal<double>(orderBook->dataObject.bids[0][1], latestBid.volume))
		{
			std::vector<Order_Book_Bids::Record> bidRecords;
			for (auto& bid : orderBook->dataObject.bids)
			{
				Order_Book_Bids::Record bidRecord;
				bidRecord.price = bid[0];
				bidRecord.volume = bid[1];
				bidRecords.push_back(bidRecord);
			}
			dataBase->order_Book_BidsTable->clear();
 			dataBase->order_Book_BidsTable->insertMultiple(bidRecords);
		}

	}

	void Fyb::executePendingOrders(Poco::Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<PendingOrders> orderBook = fybApi.GetPendingOrders();

		if (orderBook->dataObject.isSetError() && orderBook->dataObject.error != 0)
		{
			return;
		}

		std::vector<My_Pending_Buy_Orders::Record> buyRecords;
		std::vector<My_Pending_Sell_Orders::Record> sellRecords;
		for (auto& order : orderBook->dataObject.orders)
		{
			if (order.type == 'B')
			{
				My_Pending_Buy_Orders::Record rec;
				rec.amt = order.qty;
				rec.date = (Int32)order.date;
				rec.price = order.price;
				rec.ticket = order.ticket;
				buyRecords.push_back(rec);
			}
			else if (order.type == 'S')
			{
				My_Pending_Sell_Orders::Record rec;
				rec.amt = order.qty;
				rec.date = (Int32)order.date;
				rec.price = order.price;
				rec.ticket = order.ticket;
				sellRecords.push_back(rec);
			}
		}

		dataBase->my_Pending_Buy_OrdersTable->clear();
		dataBase->my_Pending_Sell_OrdersTable->clear();

		if (!buyRecords.empty())
			dataBase->my_Pending_Buy_OrdersTable->insertMultipleUnique(buyRecords);

		if (!sellRecords.empty())
			dataBase->my_Pending_Sell_OrdersTable->insertMultipleUnique(sellRecords);
	}

	void Fyb::executeOrderHistory(Poco::Timer& timer)
	{
		(void)timer;
	}


	Fyb::~Fyb()
	{
	}

	Poco::Dynamic::Var Fyb::invoke(const std::string& httpMethod, Poco::URI& uri)
	{
		static time_t lastTimeStamp = 0;
		time_t currentTimeStamp = std::time(nullptr);
		if (lastTimeStamp == currentTimeStamp)
		{
			throw TimeoutException("Fyb Error : API executed too fast", "");
		}
		lastTimeStamp = currentTimeStamp;

		//Add timestamp
		std::ostringstream timeString;
		timeString << currentTimeStamp;
		uri.addQueryParameter(std::string("timestamp"), timeString.str());

		// Create the request URI.
		Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);
		req.add("Accept-Encoding", "gzip");

		// Sign request
		if (httpMethod == Poco::Net::HTTPRequest::HTTP_POST)
		{
			//Convert to POST
			Poco::Net::HTMLForm form(req);
			req.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
			req.setURI(uri.getPath());
			form.setEncoding(Poco::Net::HTMLForm::ENCODING_URL);

			//Key
			req.set("key", fybApi.config.dataObject.consumer_key);

			//Sign
			std::ostringstream paramStream;
			form.write(paramStream);
			std::string signatureBase = paramStream.str();
			std::string signingKey = fybApi.config.dataObject.consumer_secret;
			Poco::HMACEngine<Poco::SHA1Engine> hmacEngine(signingKey);
			hmacEngine.update(signatureBase);
			Poco::DigestEngine::Digest digest = hmacEngine.digest();
			std::ostringstream digestHexBin;
			Poco::HexBinaryEncoder hexBinEncoder(digestHexBin);
			hexBinEncoder.write(reinterpret_cast<char*>(&digest[0]), digest.size());
			hexBinEncoder.close();
			req.set("sig", digestHexBin.str());

			//Submit
			form.prepareSubmit(req);
			std::ostream& ostr = session.sendRequest(req);
			form.write(ostr);
		}
		else
		{
			session.sendRequest(req);
		}

		Poco::Logger::get("Logs").information("Send Request: %s", uri.toString());

		// Receive the response.
		Poco::Net::HTTPResponse res;
		std::istream& rs = session.receiveResponse(res);

		Poco::InflatingInputStream inflater(rs, Poco::InflatingStreamBuf::STREAM_GZIP);
		// Parse the JSON
		Poco::JSON::Parser parser;
		parser.parse(inflater);
		Poco::Dynamic::Var result = parser.result();
		std::string resultString = Poco::Dynamic::Var::toString(result);
		Poco::Logger::get("Logs").information("Received Response: %s", resultString);

		// If everything went fine, return the JSON document.
		// Otherwise throw an exception.
		if (res.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			return result;
		}
		else
		{
			throw ApplicationException("Fyb Error", "");
		}
	}
}
