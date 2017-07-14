#include "stdafx.h"
#include "exchangeratelabapi.h"
#include "exchangeratelabconfig.h"
#include "exchangeratelab.h"

namespace trader {

	Exchangeratelab::Exchangeratelab()
	{
	}

	Exchangeratelab::~Exchangeratelab()
	{
	}

	Poco::Dynamic::Var Exchangeratelab::invoke(const std::string& httpMethod, Poco::URI& uri)
	{
		(void)httpMethod;
		trader::ExchangeratelabApi& exchangeratelabApi = *((trader::ExchangeratelabApi*)this);

		//Add API key
		std::ostringstream apiKeyString;
		apiKeyString << exchangeratelabApi.config.dataObject.api_key;
		uri.addQueryParameter(std::string("apikey"), apiKeyString.str());

		// Create the request URI.
		Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);

		session.sendRequest(req);

		Poco::Logger::get("Logs").information("Send Request: %s", uri.toString());

		// Receive the response.
		Poco::Net::HTTPResponse res;
		std::istream& rs = session.receiveResponse(res);

		// Parse the JSON
		Poco::JSON::Parser parser;
		parser.parse(rs);
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
			throw Poco::ApplicationException("Exchangeratelab Error", "");
		}
	}
}
