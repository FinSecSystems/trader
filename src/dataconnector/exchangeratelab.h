///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="exchangeratelab.h" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Declares the exchangeratelab class</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "api.h"
#include "db.h"
#include "exchangeratelabapi.h"
#include "interface.h"

namespace trader
{

    namespace ExchangeratelabApi
    {
        class EndPoints;
    };

    class Exchangeratelab;

    /// <summary> An exchangeratelab connection. </summary>
    class ExchangeratelabConnection : public Interface::CallConnection, public Poco::Runnable
    {
      public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the ExchangeratelabConnection class. </summary>
        ///
        /// <param name="connectionid"> The connectionid. </param>
        /// <param name="_exchange">    [in,out] If non-null, the exchange. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ExchangeratelabConnection(const std::string &connectionid, Exchangeratelab *_exchange)
            : exchange(_exchange)
        {
            (void)connectionid;
        }

        /// <summary> Runs this object. </summary>
        void run() {}

      private:
        Exchangeratelab *exchange;  ///< The exchange
    };

    /// <summary> An exchangeratelab. </summary>
    class Exchangeratelab : public Api
    {
      public:
        /// <summary> Initializes a new instance of the Exchangeratelab class. </summary>
        Exchangeratelab();

        /// <summary> Finalizes an instance of the Exchangeratelab class. </summary>
        ~Exchangeratelab();

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

        ExchangeratelabApi::EndPoints api;  ///< The API

      protected:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the Exchangeratelab class. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Exchangeratelab(const Exchangeratelab &);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Assignment operator. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///
        /// <returns> A shallow copy of this object. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Exchangeratelab &operator=(const Exchangeratelab &);
    };

} // namespace trader
