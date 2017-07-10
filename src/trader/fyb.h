#pragma once


class Fyb
	/// Base class for api
	/// (see <http://http://docs.fyb.apiary.io/#> for more information).
	/// 
{
public:
	Fyb();

	~Fyb();
		/// Destroys the Twitter object.
		
	virtual void login(const std::string& consumerKey, const std::string& consumerSecret);
		/// Specifies the OAuth authentication information used in all API calls.
		

	virtual Poco::Dynamic::Var invoke(const std::string& httpMethod, const Poco::URI& uri);
		/// Invokes the given method of the Twitter API, using the parameters
		/// given in the Poco::Net::HTMLForm object. httpMethod must be GET or POST,
		/// according to the Twitter API documentation.
		///
		/// Returns a Poco::Util::JSONConfiguration with the server's response if the
		/// server's HTTP response status code is 200 (OK).
		/// Otherwise, throws a Poco::ApplicationException.
	

protected:
	Fyb(const Fyb&);
	Fyb& operator = (const Fyb&);
	
	std::string _uri;
	std::string _consumerKey;
	std::string _consumerSecret;
};
