#pragma once

#include "db.h"
#include "api.h"
#include "krakenapi.h"
#include "krakendatabase.h"
#include "interface.h"

namespace trader {

    namespace KrakenApi {
        class EndPoints;
    };

    namespace KrakenDatabase {
        class Tables;
    };

    class Kraken;

    class KrakenConnection : public Interface::CallConnection, public Poco::Runnable
    {
    public:
        KrakenConnection(const std::string& connectionid, Kraken* _exchange)
            : exchange(_exchange)
        {
            (void)connectionid;
        }

        void run() {}

    private:
        Kraken* exchange;
    };

	class Kraken : public Api
	{
	public:
        Kraken();

		~Kraken();

		Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

		void run();
		void execute(Poco::Timer& timer);

        KrakenApi::EndPoints api;

        static AutoPtr<Interface::Connection> getConnection(const std::string& connectionId);

	protected:
        Kraken(const Kraken&);
        Kraken& operator = (const Kraken&);

		std::string _uri;

	private:
		Poco::Timer executeTimer;
		Poco::AutoPtr<KrakenDatabase::Tables> dataBase;
		//Poco::AutoPtr<trader::Db> app;
		std::vector<std::function<void(Poco::Timer&)>> serialExecutionList;
	};

}
