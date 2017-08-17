#pragma once

#include "api.h"
#include "exchangeratelabapi.h"

namespace trader {

        class ExchangeratelabApi::EndPoints;

        class Exchangeratelab : public Api
        {
        public:
            Exchangeratelab(Poco::AutoPtr<trader::App> _app);

            ~Exchangeratelab();

            Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

            ExchangeratelabApi::EndPoints api;
        protected:
            Exchangeratelab(const Exchangeratelab&);
            Exchangeratelab& operator = (const Exchangeratelab&);

        };

}