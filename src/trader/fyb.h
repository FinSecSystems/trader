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
		void executeOrderBook(Poco::Timer& timer);
		void executePendingOrders(Poco::Timer& timer);
		void executeOrderHistory(Poco::Timer& timer);

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
		Poco::Timer executeOrderBookTimer;
		Poco::Timer executePendingOrderTimer;
		Poco::Timer executeOrderHistoryTimer;
		Poco::AutoPtr<FybDatabase> dataBase;
	};

}
