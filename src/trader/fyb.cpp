#include "stdafx.h"
#include "fyb.h"
#include "fybapi.h"
#include "fybconfig.h"

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;

namespace trader {

	Fyb::Fyb()
		: fybApi(*((trader::FybApi*)this))
		, executeTickerDetailedTimer(0,5000)
		, executeAccountInfoTimer(500, 5000)
	{
	}

	void Fyb::run()
	{
		db = fybApi._app->dbSession;

		// Create table
		*db << "CREATE TABLE IF NOT EXISTS Fyb_Ticker_Detailed (TimeStamp INTEGER, Ask REAL, Bid REAL, Last REAL, Vol REAL)", now;
		*db << "CREATE UNIQUE INDEX IF NOT EXISTS Fyb_Ticker_Detailed_Index on Fyb_Ticker_Detailed(TimeStamp)", now;

		*db << "CREATE TABLE IF NOT EXISTS Fyb_Account_Balance (TimeStamp INTEGER, BTC REAL, SGD REAL)", now;
		*db << "CREATE UNIQUE INDEX IF NOT EXISTS Fyb_Account_Balance_Index on Fyb_Account_Balance(TimeStamp)", now;

		*db << "CREATE TABLE IF NOT EXISTS Fyb_Account_Info (Account_Number TEXT, BTC_Address TEXT, Email TEXT)", now;
		
		executeTickerDetailedTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeTickerDetailed));
		executeAccountInfoTimer.start(TimerCallback<Fyb>(*this, &Fyb::executeAccountInfo));
	}

	void Fyb::executeTickerDetailed(Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<trader::TickerDetailed> tickerDetailedData = fybApi.GetTickerDetailed();

		Statement insert(*db);
		insert << "INSERT INTO Fyb_Ticker_Detailed VALUES(?, ?, ?, ?, ?)",
			bind(std::time(nullptr)),
			use(tickerDetailedData->dataObject.ask),
			use(tickerDetailedData->dataObject.bid),
			use(tickerDetailedData->dataObject.last),
			use(tickerDetailedData->dataObject.vol);
		insert.execute();
	}

	void Fyb::executeAccountInfo(Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<trader::AccountInfo> accountInfo = fybApi.GetAccountInfo();

		Statement insert(*db);
		insert << "INSERT INTO Fyb_Account_Balance VALUES(?, ?, ?)",
			bind(std::time(nullptr)),
			use(accountInfo->dataObject.btcBal),
			use(accountInfo->dataObject.sgdBal);
		insert.execute();

		Poco::Int32 count;
		*db << "SELECT count(*) FROM Fyb_Account_Info",
			into(count),
			now;

		if (!count)
		{
			std::ostringstream accountInfoStream;
			accountInfoStream << "FYB" << accountInfo->dataObject.accNo;
			Statement insertAccountInfo(*db);
			insertAccountInfo << "INSERT INTO Fyb_Account_Info VALUES(?, ?, ?)",
				use(accountInfoStream.str()),
				use(accountInfo->dataObject.btcDeposit),
				use(accountInfo->dataObject.email);
			insertAccountInfo.execute();
		}
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
