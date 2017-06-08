//
// Fyb.cpp
//
// $Id: //poco/1.4/Net/samples/FybClient/src/Fyb.cpp#2 $
//
// A C++ implementation of a Fyb client based on the POCO Net library.
//
// Copyright (c) 2009-2013, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "stdafx.h"
#include "fyb.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/OAuth10Credentials.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/URI.h"
#include "Poco/Format.h"
#include "Poco/StreamCopier.h"


const std::string Fyb::FYB_URI("https://www.fybsg.com/api/SGD/");


Fyb::Fyb():
	_uri(FYB_URI)
{
}

	
Fyb::Fyb(const std::string& FybURI):
	_uri(FybURI)
{
}

	
Fyb::~Fyb()
{
}


void Fyb::login(const std::string& consumerKey, const std::string& consumerSecret, const std::string& token, const std::string& tokenSecret)
{
	_consumerKey    = consumerKey;
	_consumerSecret = consumerSecret;
	_token          = token;
	_tokenSecret    = tokenSecret;
}

	
Poco::Int64 Fyb::update(const std::string& status)
{
	Poco::Net::HTMLForm form;
	form.set("status", status);
	Poco::AutoPtr<Poco::Util::AbstractConfiguration> pResult = invoke(Poco::Net::HTTPRequest::HTTP_POST, "update", &form);
	return pResult->getInt64("id", 0);
}

double Fyb::tickerdetailed()
{
    Poco::AutoPtr<Poco::Util::AbstractConfiguration> pResult = invoke(Poco::Net::HTTPRequest::HTTP_GET, "tickerdetailed");
    return pResult->getDouble("Ask", 0);
}


Poco::AutoPtr<Poco::Util::AbstractConfiguration> Fyb::invoke(const std::string& httpMethod, const std::string& FybMethod, Poco::Net::HTMLForm* form)
{
	// Create the request URI.
	// We use the JSON version of the Fyb API.
	Poco::URI uri(_uri + FybMethod + ".json");
	
	Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
	Poco::Net::HTTPRequest req(httpMethod, uri.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);
	
	// Sign request
    if (form)
    {
        Poco::Net::OAuth10Credentials creds(_consumerKey, _consumerSecret);// , _token, _tokenSecret);
        creds.authenticate(req, uri, *form);
        // Send the request.
        form->prepareSubmit(req);
        std::ostream& ostr = session.sendRequest(req);
        form->write(ostr);
    }
    else
    {
        session.sendRequest(req);
    }
	
	// Receive the response.
	Poco::Net::HTTPResponse res;
	std::istream& rs = session.receiveResponse(res);
	
	Poco::AutoPtr<Poco::Util::JSONConfiguration> pResult = new Poco::Util::JSONConfiguration(rs);

	// If everything went fine, return the JSON document.
	// Otherwise throw an exception.
	if (res.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
	{
		return pResult;
	}
	else
	{
		throw Poco::ApplicationException("Fyb Error", pResult->getString("errors[0].message", ""));
	}
}
