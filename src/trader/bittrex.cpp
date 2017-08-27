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

	string getHMAC2(string keyParam, string message)
	{
		char key[10000];
		char data[10000];
		strcpy(key, keyParam.c_str());
		strncpy(data, message.c_str(), sizeof(data));

		unsigned char* digest;
		digest = HMAC(EVP_sha512(), key, (int)strlen(key), (unsigned char*)data, (int)strlen(data), NULL, NULL);
		char mdString[SHA512_DIGEST_LENGTH*2+1];
		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
			sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
		mdString[SHA512_DIGEST_LENGTH * 2] = '\0';

		string output = mdString;
		return output;
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
			req.set("apisign", getHMAC2(api.config.dataObject.api_secret, uri.toString()));
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
