#pragma once

#include "dataconnector/db.h"
#include "dataconnector/api.h"
#include "exchangeratelabapi.h"

namespace trader {

        namespace ExchangeratelabApi {
            class EndPoints;
        };

        class Exchangeratelab : public Api
        {
        public:
            Exchangeratelab(Poco::AutoPtr<trader::Db> _app);

            ~Exchangeratelab();

            Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

            ExchangeratelabApi::EndPoints api;
        protected:
            Exchangeratelab(const Exchangeratelab&);
            Exchangeratelab& operator = (const Exchangeratelab&);

        };

}