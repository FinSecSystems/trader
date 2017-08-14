#include "stdafx.h"
#include "kraken.h"
#include "api.h"
#include "krakenconfig.h"
#include "krakendatabase.h"
#include "helper.h"

namespace trader {

    Kraken::Kraken(AutoPtr<trader::App> _app)
		: api(_app, this)
		, app(_app)
		, dataBase(new KrakenDatabase(_app->dbSession))
		, executeTimer(0, 1000)
	{
	}

	void Kraken::run()
	{
		dataBase->init();
		//dataBase->clear();

		executeTimer.start(TimerCallback<Kraken>(*this, &Kraken::execute));
	}

	void Kraken::execute(Timer& timer)
	{
		static std::atomic_int32_t idx = 0;
        if (serialExecutionList.size())
        {
            serialExecutionList[idx % serialExecutionList.size()](timer);
            ++idx;
        }
	}

    Kraken::~Kraken()
	{
	}

	Dynamic::Var Kraken::invoke(const std::string& httpMethod, URI& uri)
	{
		static FastMutex lock;
		static time_t lastTimeStamp = 0;
		time_t currentTimeStamp;
		if (lock.tryLock())
		{
			currentTimeStamp = std::time(nullptr);
			if (lastTimeStamp == currentTimeStamp)
			{
				throw TimeoutException("Kraken Error : API executed too fast", "");
			}
			lastTimeStamp = currentTimeStamp;
			lock.unlock();
		}
		else
		{
			throw TimeoutException("Kraken Error : API executed too fast", "");
		}

		// Create the request URI.
		HTTPSClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);
		req.add("Accept-Encoding", "gzip");

		// Sign request
		if (httpMethod == HTTPRequest::HTTP_POST)
		{
			//Convert to POST
			HTMLForm form(req);
			req.setMethod(HTTPRequest::HTTP_POST);
			req.setURI(uri.getPath());
			form.setEncoding(HTMLForm::ENCODING_URL);

			//Key
			req.set("API-Key", api.config.dataObject.api_key);

			//Sign
			ostringstream paramStream;
			form.write(paramStream);
			string signatureBase = paramStream.str();
			string signingKey = api.config.dataObject.private_key;
			HMACEngine<SHA2Engine> hmacEngine(signingKey);
			hmacEngine.update(signatureBase);
			DigestEngine::Digest digest = hmacEngine.digest();
			std::ostringstream digestHexBin;
			HexBinaryEncoder hexBinEncoder(digestHexBin);
			hexBinEncoder.write(reinterpret_cast<char*>(&digest[0]), digest.size());
			hexBinEncoder.close();
			req.set("sig", digestHexBin.str());

			//Submit
			form.prepareSubmit(req);
			ostream& ostr = session.sendRequest(req);
			form.write(ostr);
		}
		else
		{
			session.sendRequest(req);
		}

		Logger::get("Logs").information("Send Request: %s", uri.toString());

		// Receive the response.
		HTTPResponse res;
		istream& rs = session.receiveResponse(res);

		InflatingInputStream inflater(rs, InflatingStreamBuf::STREAM_GZIP);
		// Parse the JSON
		JSON::Parser parser;
		parser.parse(inflater);
		Dynamic::Var result = parser.result();
		string resultString = Dynamic::Var::toString(result);
		Logger::get("Logs").information("Received Response: %s", resultString);

		// If everything went fine, return the JSON document.
		// Otherwise throw an exception.
		if (res.getStatus() == HTTPResponse::HTTP_OK)
		{
            Poco::AutoPtr<ErrorIntrospector> errorMsgs = new ErrorIntrospector();
            errorMsgs->read(result);
            if (errorMsgs->dataObject.error.size())
            {
                throw ApplicationException("Kraken Error", "Received Error Response");
            }
			return result;
		}
		else
		{
			throw ApplicationException("Kraken Error", "");
		}
	}
}
