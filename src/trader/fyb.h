#pragma once

#include "fybdatabase.h"

namespace trader {

	class FybApi;

	class Fyb
	{
	public:
		Fyb();

		~Fyb();

		virtual Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

		void run();

		void executeTickerDetailed(Poco::Timer& timer);
		void executeAccountInfo(Poco::Timer& timer);
		void executeTradeHistory(Poco::Timer& timer);

	protected:
		Fyb(const Fyb&);
		Fyb& operator = (const Fyb&);

		std::string _uri;
		std::string _consumerKey;
		std::string _consumerSecret;

	private:
		FybApi& fybApi;
		Poco::Data::Session* db;
		Poco::Timer executeTickerDetailedTimer;
		Poco::Timer executeAccountInfoTimer;
		Poco::Timer executeTradeHistoryTimer;
		Poco::AutoPtr<FybDatabase> dataBase;
	};

}
