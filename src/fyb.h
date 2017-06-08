#pragma once


#include "Poco/Poco.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"


class Fyb
	/// A simple implementation of a Twitter API client
	/// (see <http://http://docs.fyb.apiary.io/#> for more information).
	/// 
{
public:
    Fyb();
		/// Creates the Twitter object, using
		/// the default Twitter API URI (<http://api.twitter.com/1.1/statuses/>).
		
    Fyb(const std::string& URI);
		/// Creates the Twitter object using the given Twitter API URI.
		
	~Fyb();
		/// Destroys the Twitter object.
		
	void login(const std::string& consumerKey, const std::string& consumerSecret, const std::string& token, const std::string& tokenSecret);
		/// Specifies the OAuth authentication information used in all API calls.
		
	Poco::Int64 update(const std::string& status);
		/// Updates the user's status.
		///
		/// Returns the ID of the newly created status.

    double tickerdetailed();

	Poco::AutoPtr<Poco::Util::AbstractConfiguration> invoke(const std::string& httpMethod, const std::string& twitterMethod, Poco::Net::HTMLForm* params = nullptr);
		/// Invokes the given method of the Twitter API, using the parameters
		/// given in the Poco::Net::HTMLForm object. httpMethod must be GET or POST,
		/// according to the Twitter API documentation.
		///
		/// Returns a Poco::Util::JSONConfiguration with the server's response if the
		/// server's HTTP response status code is 200 (OK).
		/// Otherwise, throws a Poco::ApplicationException.
	
	static const std::string FYB_URI;

private:
    Fyb(const Fyb&);
    Fyb& operator = (const Fyb&);
	
	std::string _uri;
	std::string _consumerKey;
	std::string _consumerSecret;
	std::string _token;
	std::string _tokenSecret;
};
