///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="bittrex.h" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Declares the Bittrex class</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        /// <summary> An end points. </summary>
        class EndPoints;
    };


    namespace BittrexDatabase
    {
        /// <summary> A tables. </summary>
        class Tables;
    };

    /// <summary> A bittrex. </summary>
    class Bittrex : public Api
    {
      public:
        /// <summary> Initializes a new instance of the Bittrex class. </summary>
        Bittrex();

        /// <summary> Runs this object. </summary>
        void run();

        /// <summary> Finalizes an instance of the Bittrex class. </summary>
        ~Bittrex();

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Executes the given operation on a different thread, and waits for the result. </summary>
        ///
        /// <param name="httpMethod"> The HTTP method. </param>
        /// <param name="uri">		  [in,out] URI of the document. </param>
        ///
        /// <returns> A Poco::Dynamic::Var. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Poco::Dynamic::Var invoke(const std::string &httpMethod, Poco::URI &uri);

        BittrexApi::EndPoints api;  ///< The API

        Poco::AutoPtr< BittrexDatabase::Tables > dataBase;  ///< The data base

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Sets the parameters. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setParams(const std::string&);

      protected:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Initializes a new instance of the Bittrex class. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Bittrex(const Bittrex &);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary> Assignment operator. </summary>
        ///
        /// <param name="parameter1"> The first parameter. </param>
        ///
        /// <returns> A shallow copy of this object. </returns>
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Bittrex &operator=(const Bittrex &);
        Poco::UInt32 configurationIdx;  ///< Zero-based index of the configuration
    };

} // namespace trader
