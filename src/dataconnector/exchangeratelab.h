#pragma once

#include "db.h"
#include "api.h"
#include "exchangeratelabapi.h"
#include "interface.h"

namespace trader {

        namespace ExchangeratelabApi {
            class EndPoints;
        };

        class Exchangeratelab;

        class ExchangeratelabConnection : public Interface::Connection
        {
        public:
            ExchangeratelabConnection(const std::string& connectionid, Exchangeratelab* _exchange)
                : exchange(_exchange)
            {
                (void)connectionid;
            }
        private:
            Exchangeratelab* exchange;
        };

        class Exchangeratelab : public Api
        {
        public:
            Exchangeratelab();

            ~Exchangeratelab();

            Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

            static AutoPtr<Interface::Connection> getConnection(const std::string& connectionId);

            ExchangeratelabApi::EndPoints api;
        protected:
            Exchangeratelab(const Exchangeratelab&);
            Exchangeratelab& operator = (const Exchangeratelab&);

        };

}