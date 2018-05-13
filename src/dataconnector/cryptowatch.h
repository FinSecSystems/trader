///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="cryptowatch.h" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Declares Cryptowatch class</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "api.h"
#include "cryptowatchapi.h"
#include "cryptowatchdatabase.h"
#include "db.h"
#include "interface.h"

namespace trader
{

    namespace CryptowatchApi
    {
        class EndPoints;
    };

    namespace CryptowatchDatabase
    {
        class Tables;
    };

    class Cryptowatch;

    /// <summary> A cryptowatch connection. </summary>
    class CryptowatchConnection : public Interface::CallConnection, public Poco::Runnable
    {
      public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the CryptowatchConnection class. </summary>
        ///
        /// <param name="connectionid"> The connectionid. </param>
        /// <param name="_exchange">    [in,out] If non-null, the exchange. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CryptowatchConnection(const std::string &connectionid, Cryptowatch *_exchange)
            : exchange(_exchange)
        {
            (void)connectionid;
        }

        /// <summary> Runs this object. </summary>
        void run() {}

      private:
        Cryptowatch *exchange;  ///< The exchange
    };

    /// <summary> A cryptowatch. </summary>
    class Cryptowatch : public Api
    {
      public:
        /// <summary> Initializes a new instance of the Cryptowatch class. </summary>
        Cryptowatch();

        /// <summary> Finalizes an instance of the Cryptowatch class. </summary>
        ~Cryptowatch();

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Executes the given operation on a different thread, and waits for the result. </summary>
        ///
        /// <param name="httpMethod"> The HTTP method. </param>
        /// <param name="uri">		  [in,out] URI of the document. </param>
        ///
        /// <returns> A Poco::Dynamic::Var. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Poco::Dynamic::Var invoke(const std::string &httpMethod, Poco::URI &uri);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Gets a connection. </summary>
        ///
        /// <param name="connectionId"> Identifier for the connection. </param>
        ///
        /// <returns> The connection. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static AutoPtr< Interface::Connection > getConnection(const std::string &connectionId);

        CryptowatchApi::EndPoints api;  ///< The API

        Poco::AutoPtr< CryptowatchDatabase::Tables > dataBase;  ///< The data base

      protected:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the Cryptowatch class. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Cryptowatch(const Cryptowatch &);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Assignment operator. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///
        /// <returns> A shallow copy of this object. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Cryptowatch &operator=(const Cryptowatch &);
    };

} // namespace trader
