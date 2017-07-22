#include "stdafx.h"
#include "fyb.h"
#include "fybapi.h"
#include "fybconfig.h"
#include "fybdatabase.h"

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

namespace trader {

	Fyb::Fyb()
		: fybApi(*((FybApi*)this))
		, executeTickerDetailedTimer(0,5000)
		, executeAccountInfoTimer(500, 5000)
		, executeTradeHistoryTimer(1000, 5000)
	{
	}

	void Fyb::run()
	{
		db = fybApi._app->dbSession;

		dataBase = new FybDatabase(db);
		dataBase->init();
	
		executeTickerDetailedTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeTickerDetailed));
		executeAccountInfoTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeAccountInfo));
		executeTradeHistoryTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeTradeHistory));
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
		if (currentRec.tid != 0)
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
		dataBase->trade_HistoryTable->insertMultiple(tradeHistoryRecord);
	}

	Fyb::~Fyb()
	{
	}

	Poco::Dynamic::Var Fyb::invoke(const std::string& httpMethod, Poco::URI& uri)
	{
		//Add timestamp
		std::ostringstream timeString;
		timeString << std::time(nullptr);
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
			throw Poco::ApplicationException("Fyb Error", "");
		}
	}
}
