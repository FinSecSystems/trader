#pragma once

#include "api.h"
#include "db.h"
#include "fybapi.h"
#include "fybdatabase.h"
#include "interface.h"

namespace trader
{

    namespace FybApi
    {
        class EndPoints;
    };

    namespace FybDatabase
    {
        class Tables;
    };

    class Fyb : public Api
    {
      public:
        Fyb();

        ~Fyb();

        Poco::Dynamic::Var invoke(const std::string &httpMethod, Poco::URI &uri);

		void setParams(const std::string&);

        void run();
        void execute(Poco::Timer &timer);

        void executeTradeHistory(Poco::Timer &timer);
        void executeOrderBook(Poco::Timer &timer);
        void executePendingOrders(Poco::Timer &timer);
        void executeOrderHistory(Poco::Timer &timer);

        FybApi::EndPoints api;

        static AutoPtr< Interface::Connection > getConnection(const std::string &connectionId);

      protected:
        Fyb(const Fyb &);
        Fyb &operator=(const Fyb &);

        std::string _uri;

      private:
        Poco::Timer executeTimer;
        Poco::AutoPtr< FybDatabase::Tables > dataBase;
        Poco::AutoPtr< trader::Db > app;
        std::vector< std::function< void(Poco::Timer &) > > serialExecutionList;
		Poco::UInt32 configurationIdx;
    };

} // namespace trader
