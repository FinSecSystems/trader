// ***********************************************************************
// Assembly         : trader
// Author           : Viknash
// ***********************************************************************
// <copyright file="bittrex.h" >
//     Copyright (c) FinSec Systems. All rights reserved.
// </copyright>
// <summary>
//     Communication interface with the Bittrex exchange
// </summary>
// ***********************************************************************
#pragma once

#include "api.h"
#include "app.h"
#include "bittrexapi.h"
#include "bittrexdatabase.h"
#include "db.h"
#include "interface.h"
#include "interfacehelper.h"

namespace trader
{

    namespace BittrexApi
    {
        class EndPoints;
    };

    namespace BittrexDatabase
    {
        class Tables;
    };

    class Bittrex : public Api
    {
      public:
        Bittrex();

        void run();

        ~Bittrex();

        Poco::Dynamic::Var invoke(const std::string &httpMethod, Poco::URI &uri);

        BittrexApi::EndPoints api;

        Poco::AutoPtr< BittrexDatabase::Tables > dataBase;

      protected:
        Bittrex(const Bittrex &);
        Bittrex &operator=(const Bittrex &);
    };

} // namespace trader
