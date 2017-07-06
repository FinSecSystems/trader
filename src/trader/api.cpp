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
#include "api.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/OAuth10Credentials.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/URI.h"
#include "Poco/Format.h"
#include "Poco/StreamCopier.h"


Api::Api()
{
}

	
Api::~Api()
{
}


void Api::login(const std::string& consumerKey, const std::string& consumerSecret, const std::string& token, const std::string& tokenSecret)
{
	_consumerKey    = consumerKey;
	_consumerSecret = consumerSecret;
	_token          = token;
	_tokenSecret    = tokenSecret;
}


Poco::Dynamic::Var  Api::invoke(const std::string& httpMethod, const Poco::URI& uri)
{
	// Create the request URI.
	// We use the JSON version of the Fyb API.
	
	Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);
	
	// Sign request
    if (httpMethod == Poco::Net::HTTPRequest::HTTP_POST)
    {
		Poco::Net::HTMLForm form(req);
		req.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
		form.setEncoding(Poco::Net::HTMLForm::ENCODING_URL);
        Poco::Net::OAuth10Credentials creds(_consumerKey, _consumerSecret);// , _token, _tokenSecret);
        creds.authenticate(req, uri, form);
        // Send the request.45731
        form.prepareSubmit(req);
        std::ostream& ostr = session.sendRequest(req);
        form.write(ostr);
    }
    else
    {
        session.sendRequest(req);
    }
	
	// Receive the response.
	Poco::Net::HTTPResponse res;
	std::istream& rs = session.receiveResponse(res);
	
	//Poco::AutoPtr<Poco::Util::JSONConfiguration> pResult = new Poco::Util::JSONConfiguration(rs);

	Poco::JSON::Parser parser;
	parser.parse(rs);
	Poco::Dynamic::Var result = parser.result();
	//Poco::JSON::Object::Ptr obj = result.extract<Poco::JSON::Object::Ptr>();

	// If everything went fine, return the JSON document.
	// Otherwise throw an exception.
	if (res.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
	{
		return result;
	}
	else
	{
		throw Poco::ApplicationException("Api Error", "");
	}
}
