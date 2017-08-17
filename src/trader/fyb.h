#pragma once

#include "api.h"
#include "fybapi.h"
#include "fybdatabase.h"

namespace trader {

	class FybApi::EndPoints;

	class Fyb : public Api
	{
	public:
		Fyb(Poco::AutoPtr<trader::App> _app);

		~Fyb();

		Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

		void run();
		void execute(Poco::Timer& timer);

		void executeTickerDetailed(Poco::Timer& timer);
		void executeAccountInfo(Poco::Timer& timer);
		void executeTradeHistory(Poco::Timer& timer);
		void executeOrderBook(Poco::Timer& timer);
		void executePendingOrders(Poco::Timer& timer);
		void executeOrderHistory(Poco::Timer& timer);

        FybApi::EndPoints api;

	protected:
		Fyb(const Fyb&);
		Fyb& operator = (const Fyb&);

		std::string _uri;

	private:
		Poco::Timer executeTimer;
		Poco::AutoPtr<FybDatabase> dataBase;
		Poco::AutoPtr<trader::App> app;
		std::vector<std::function<void(Poco::Timer&)>> serialExecutionList;
	};

}
