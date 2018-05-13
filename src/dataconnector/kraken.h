///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="kraken.h" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Kraken Api connection declaration</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "api.h"
#include "db.h"
#include "interface.h"
#include "krakenapi.h"
#include "krakendatabase.h"

namespace trader
{

    namespace KrakenApi
    {
        class EndPoints;
    };

    namespace KrakenDatabase
    {
        class Tables;
    };

    class Kraken;

    /// <summary> A kraken connection. </summary>
    class KrakenConnection : public Interface::CallConnection, public Poco::Runnable
    {
      public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the KrakenConnection class. </summary>
        ///
        /// <param name="connectionid"> The connectionid. </param>
        /// <param name="_exchange">    [in,out] If non-null, the exchange. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        KrakenConnection(const std::string &connectionid, Kraken *_exchange)
            : exchange(_exchange)
        {
            (void)connectionid;
        }

        /// <summary> Runs this object. </summary>
        void run() {}

      private:
        Kraken *exchange;   ///< The exchange
    };

    /// <summary> A kraken. </summary>
    class Kraken : public Api
    {
      public:
        /// <summary> Initializes a new instance of the Kraken class. </summary>
        Kraken();

        /// <summary> Finalizes an instance of the Kraken class. </summary>
        ~Kraken();

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Executes the given operation on a different thread, and waits for the result. </summary>
        ///
        /// <param name="httpMethod"> The HTTP method. </param>
        /// <param name="uri">		  [in,out] URI of the document. </param>
        ///
        /// <returns> A Poco::Dynamic::Var. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Poco::Dynamic::Var invoke(const std::string &httpMethod, Poco::URI &uri);

        /// <summary> Runs this object. </summary>
        void run();

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Executes the given timer. </summary>
        ///
        /// <param name="timer"> [in,out] The timer. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void execute(Poco::Timer &timer);

        KrakenApi::EndPoints api;   ///< The API

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Gets a connection. </summary>
        ///
        /// <param name="connectionId"> Identifier for the connection. </param>
        ///
        /// <returns> The connection. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static AutoPtr< Interface::Connection > getConnection(const std::string &connectionId);

      protected:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the Kraken class. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Kraken(const Kraken &);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Assignment operator. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///
        /// <returns> A shallow copy of this object. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Kraken &operator=(const Kraken &);

        std::string _uri;   ///< _URI of the document

      private:
        Poco::Timer executeTimer;   ///< The execute timer
        Poco::AutoPtr< KrakenDatabase::Tables > dataBase;   ///< The data base
        // Poco::AutoPtr<trader::Db> app;
        std::vector< std::function< void(Poco::Timer &) > > serialExecutionList;	///< List of serial executions
    };

} // namespace trader
