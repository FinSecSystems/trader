#pragma once


#include "Poco/Poco.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"


class Api
	/// Base class for api
	/// (see <http://http://docs.fyb.apiary.io/#> for more information).
	/// 
{
public:
    Api( const std::string& uri);

	~Api();
		/// Destroys the Twitter object.
		
	virtual void login(const std::string& consumerKey, const std::string& consumerSecret, const std::string& token, const std::string& tokenSecret);
		/// Specifies the OAuth authentication information used in all API calls.
		

	virtual Poco::AutoPtr<Poco::Util::AbstractConfiguration> invoke(const std::string& httpMethod, const std::string& method, Poco::Net::HTMLForm* params = nullptr);
		/// Invokes the given method of the Twitter API, using the parameters
		/// given in the Poco::Net::HTMLForm object. httpMethod must be GET or POST,
		/// according to the Twitter API documentation.
		///
		/// Returns a Poco::Util::JSONConfiguration with the server's response if the
		/// server's HTTP response status code is 200 (OK).
		/// Otherwise, throws a Poco::ApplicationException.
	

protected:
    Api(const Api&);
    Api& operator = (const Api&);
	
	std::string _uri;
    std::string _extension;
	std::string _consumerKey;
	std::string _consumerSecret;
	std::string _token;
	std::string _tokenSecret;
};
