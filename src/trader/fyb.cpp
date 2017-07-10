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


Fyb::Fyb()
{
}

	
Fyb::~Fyb()
{
}


void Fyb::login(const std::string& consumerKey, const std::string& consumerSecret)
{
	_consumerKey    = consumerKey;
	_consumerSecret = consumerSecret;
}

std::string percentEncode(const std::string& str)
{
	std::string encoded = str;
	//Poco::URI::encode(str, "!?#/'\",;:$&()[]*+=@", encoded);
	return encoded;
}

Poco::Dynamic::Var Fyb::invoke(const std::string& httpMethod, const Poco::URI& uri)
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
        //Poco::Net::OAuth10Credentials creds(_consumerKey, _consumerSecret);// , _token, _tokenSecret);
        //creds.authenticate(req, uri, form);
        // Send the request.45731

		req.set("key", _consumerKey);
#if 0
		std::map<std::string, std::string> paramsMap;
		for (Poco::Net::HTMLForm::ConstIterator it = form.begin(); it != form.end(); ++it)
		{
			paramsMap[percentEncode(it->first)] = percentEncode(it->second);
		}
		std::string paramsString;
		for (std::map<std::string, std::string>::const_iterator it = paramsMap.begin(); it != paramsMap.end(); ++it)
		{
			if (it != paramsMap.begin()) paramsString += '&';
			paramsString += it->first;
			paramsString += "=";
			paramsString += it->second;
		}
#endif
		std::ostringstream paramStream;
		form.write(paramStream);
		std::string paramsString = paramStream.str();
		std::string signatureBase = percentEncode(paramsString);
		std::string signingKey = percentEncode(_consumerSecret);
		Poco::HMACEngine<Poco::SHA1Engine> hmacEngine(signingKey);
		hmacEngine.update(signatureBase);
		Poco::DigestEngine::Digest digest = hmacEngine.digest();
		std::ostringstream digestBase64;
		Poco::Base64Encoder base64Encoder(digestBase64);
		base64Encoder.write(reinterpret_cast<char*>(&digest[0]), digest.size());
		base64Encoder.close();

		req.set("sig", digestBase64.str());

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
	
	Poco::JSON::Parser parser;
	parser.parse(rs);
	Poco::Dynamic::Var result = parser.result();

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
