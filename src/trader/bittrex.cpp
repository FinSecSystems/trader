#include "stdafx.h"
#include "bittrex.h"
#include "bittrexapi.h"
#include "helper.h"
#include "shautils.h"

namespace trader {

    using namespace BittrexApi;

    Bittrex::Bittrex(Poco::AutoPtr<trader::App> _app)
        : api(_app, this)
    {
    }

    Bittrex::~Bittrex()
    {
    }

	std::string signature(const std::string& uri,
		const std::string& secret
	)
	{
		// add path to data to encrypt
		std::vector<unsigned char> data(uri.begin(), uri.end());
		std::vector<unsigned char> secretkey(secret.begin(), secret.end());
		// and compute HMAC
		//return b64_encode(hmac_sha512(data, secretkey));
		return b64_encode(hmac_sha512(data, b64_decode(secret)));
		//std::vector<unsigned char> sig = hmac_sha512(data, secretkey);
		//std::string retVal(sig.begin(), sig.end());
		//return retVal;
	}

    Dynamic::Var Bittrex::invoke(const string& httpMethod, URI& uri)
    {
        (void)httpMethod;

		time_t currentTimeStamp = std::time(nullptr);

		bool privateApi = (uri.getHost().find("public") == std::string::npos);

		// Sign request
		if (privateApi)
		{
			//Add api key
			uri.addQueryParameter(string("apikey"), api.config.dataObject.api_key);

			//Add nonce
			ostringstream nonceStream;
			nonceStream << currentTimeStamp;
			uri.addQueryParameter(string("nonce"), nonceStream.str());
		}

        // Create the request URI.
        HTTPSClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);

		if (privateApi)
		{
			req.set("apisign", signature(uri.toString(), api.config.dataObject.api_secret));
		}

		//Submit
		session.sendRequest(req);

        Logger::get("Logs").information("Send Request: %s", uri.toString());

        // Receive the response.
        HTTPResponse res;
        istream& rs = session.receiveResponse(res);

        // Parse the JSON
        JSON::Parser parser;
        parser.parse(rs);
        Dynamic::Var result = parser.result();
        string resultString = Dynamic::Var::toString(result);
        Logger::get("Logs").information("Received Response: %s", resultString);

        // If everything went fine, return the JSON document.
        // Otherwise throw an exception.
        if (res.getStatus() == HTTPResponse::HTTP_OK)
        {
            Poco::AutoPtr<ResultIntrospector> msg = new ResultIntrospector();
            msg->read(result);
            if (!msg->dataObject.success)
            {
                throw ApplicationException("Bittrex Error", "Received Error Response");
            }
            return result;
        }
        else
        {
            throw ApplicationException("Bittrex Error", "");
        }
    }
}
