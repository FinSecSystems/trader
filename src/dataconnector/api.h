#pragma once

namespace trader
{

    class Api
    {
      public:
        virtual ~Api(){};
        virtual Poco::Dynamic::Var invoke(const std::string &httpMethod, Poco::URI &uri) = 0;
    };
} // namespace trader
