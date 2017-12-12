#include "stdafx.h"
#include "exchangeratelab.h"
#include "exchangeratelabapi.h"
#include "exchangeratelabconfig.h"

namespace trader {

    using namespace ExchangeratelabApi;

    AutoPtr<Interface::Connection> Exchangeratelab::getConnection(const std::string& connectionId)
    {
        return new ExchangeratelabConnection(connectionId, new Exchangeratelab());
    }

	Exchangeratelab::Exchangeratelab()
		: api(AppManager::instance.get()->getApp(), this)
	{
	}

	Exchangeratelab::~Exchangeratelab()
	{
	}

	Dynamic::Var Exchangeratelab::invoke(const string& httpMethod, URI& uri)
	{
		(void)httpMethod;

		//Add API key
		ostringstream apiKeyString;
		apiKeyString << api.config.dataObject.api_key;
		uri.addQueryParameter(string("apikey"), apiKeyString.str());

		// Create the request URI.
		HTTPClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);

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
		if (res.getStatus() == Net::HTTPResponse::HTTP_OK)
		{
			return result;
		}
		else
		{
			throw ApplicationException("Exchangeratelab Error", "");
		}
	}
}
