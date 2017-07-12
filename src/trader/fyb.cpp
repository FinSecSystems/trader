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
	std::string encoded;
	Poco::URI::encode(str, "!?#/'\",;:$&()[]*+=@", encoded);
	return encoded;
}

Poco::Dynamic::Var Fyb::invoke(const std::string& httpMethod, const Poco::URI& uri)
{
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
		req.set("key", _consumerKey);

		//Sign
		std::ostringstream paramStream;
		form.write(paramStream);
		std::string signatureBase = paramStream.str();
		std::string signingKey = _consumerSecret;
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
	
	// Receive the response.
	Poco::Net::HTTPResponse res;
	std::istream& rs = session.receiveResponse(res);
	
	Poco::InflatingInputStream inflater(rs, Poco::InflatingStreamBuf::STREAM_GZIP);
	// Parse the JSON
	Poco::JSON::Parser parser;
	parser.parse(inflater);
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
