#pragma once


namespace trader {

	class FybApi;

	class Fyb
	{
	public:
		Fyb();

		~Fyb();

		virtual Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

		void executeTickerDetailed(Poco::Timer& timer);

	protected:
		Fyb(const Fyb&);
		Fyb& operator = (const Fyb&);

		std::string _uri;
		std::string _consumerKey;
		std::string _consumerSecret;

	private:
		FybApi& fybApi;
		Poco::Data::Session& db;
	};

}
