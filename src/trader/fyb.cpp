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
		, db(*fybApi._app->dbSession)
	{
		Timer timer(0, 500);
		timer.start(TimerCallback<Fyb>(*this, &Fyb::executeTickerDetailed));
	}

	void Fyb::executeTickerDetailed(Timer& timer)
	{
		(void)timer;
		Poco::AutoPtr<trader::TickerDetailed> tickerDetailedData = fybApi.GetTickerDetailed();
		// (re)create table
		db << "CREATE TABLE FybTickerDetailed (Ask REAL, Bid REAL, Last REAL, Vol REAL)", now;

		Statement insert(db);
		insert << "INSERT INTO FybTickerDetailed VALUES(?, ?, ?, ?)",
			use(tickerDetailedData->dataObject.ask),
			use(tickerDetailedData->dataObject.bid),
			use(tickerDetailedData->dataObject.last),
			use(tickerDetailedData->dataObject.vol);

		insert.execute();
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
