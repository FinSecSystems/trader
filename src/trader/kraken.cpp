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

    class SHA512Engine : public SHA2Engine
    {
    public:
        enum
        {
            BLOCK_SIZE = 128,
            DIGEST_SIZE = 512/8
        };
    };

    class SHA256Engine : public SHA2Engine
    {
    public:
        enum
        {
            BLOCK_SIZE = 64,
            DIGEST_SIZE = 256/8
        };

        SHA256Engine(std::string _str)
            : SHA2Engine(SHA_256)
        {
            updateImpl(_str.c_str(), _str.length());
        }

    };

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
            //Initialize POST Form with GET params
			HTMLForm form(req);
			form.setEncoding(HTMLForm::ENCODING_URL);

            //Convert Get request to POST
            req.setMethod(HTTPRequest::HTTP_POST);
            req.setURI(uri.getPath());

			//Key
			req.set("API-Key", api.config.dataObject.api_key);

            //Nonce
			ostringstream sha256Stream;
            int64_t nonce = std::time(nullptr);
            sha256Stream << nonce;
            sha256Stream << "nonce=";
            sha256Stream << nonce;

            //Extract POST data
            ostringstream formData;
            form.write(formData);
            if (formData.str().length())
            {
                sha256Stream << "&";
                form.write(sha256Stream);
            }

            //SHA256 of nonce and POST data
            SHA256Engine sha256(sha256Stream.str());

            //ostringstream hmac512Stream;
            //hmac512Stream << uri.getPath();
            //hmac512Stream << sha256.digest().data();
            DigestEngine::Digest hmac512Data(uri.getPath().begin(), uri.getPath().end());
            DigestEngine::Digest sha256Digest = sha256.digest();
            hmac512Data.insert(hmac512Data.end(), sha256Digest.begin(), sha256Digest.end());

            //Decode private key to base64
            std::istringstream istr(api.config.dataObject.private_key);
            Base64Decoder decoder(istr);
            std::string signingKey;
            StreamCopier::copyToString(decoder, signingKey);

            //Sign
			HMACEngine<SHA512Engine> hmacEngine(signingKey);
			hmacEngine.update(hmac512Data.data(), hmac512Data.size());

            //Encode Signature to Base64
			DigestEngine::Digest digest = hmacEngine.digest();
			std::ostringstream digestBase64;
			Base64Encoder base64Encoder(digestBase64);
            base64Encoder.write(reinterpret_cast<char*>(&digest[0]), digest.size());
            base64Encoder.close();
			req.set("API-Sign", digestBase64.str());

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
