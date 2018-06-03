#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="exchangeratelab.cpp" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>ExchangerateLab class implementation</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "exchangeratelab.h"
#include "exchangeratelabapi.h"
#include "exchangeratelabconfig.h"

namespace trader
{

    using namespace ExchangeratelabApi;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Gets a connection. </summary>
    ///
    /// <param name="connectionId"> Identifier for the connection. </param>
    ///
    /// <returns> The connection. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AutoPtr< Interface::Connection > Exchangeratelab::getConnection(const std::string &connectionId)
    {
        return new ExchangeratelabConnection(connectionId, new Exchangeratelab());
    }

    /// <summary> Initializes a new instance of the Exchangeratelab class. </summary>
    Exchangeratelab::Exchangeratelab()
        : api(AppManager::instance.getApp(), this)
    {
    }

    /// <summary> Finalizes an instance of the Exchangeratelab class. </summary>
    Exchangeratelab::~Exchangeratelab() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Executes the given operation on a different thread, and waits for the result. </summary>
    ///
    /// <exception cref="ApplicationException"> Thrown when an Application error condition occurs. </exception>
    ///
    /// <param name="httpMethod"> The HTTP method. </param>
    /// <param name="uri">		  [in,out] URI of the document. </param>
    ///
    /// <returns> A Dynamic::Var. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Dynamic::Var Exchangeratelab::invoke(const string &httpMethod, URI &uri)
    {
        (void)httpMethod;

        // Add API key
        ostringstream apiKeyString;
        apiKeyString << api.config.dataObject.api_key;
        uri.addQueryParameter(string("apikey"), apiKeyString.str());

        // Create the request URI.
        HTTPClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);

        session.sendRequest(req);

        Logger::get("Logs").information("Send Request: %s", uri.toString());

        // Receive the response.
        HTTPResponse res;
        istream &rs = session.receiveResponse(res);

        // Parse the JSON
        JSON::Parser parser;
        parser.parse(rs);
        Dynamic::Var result = parser.result();
        string resultString = Dynamic::Var::toString(result);
        Logger::get("Logs").information("Received Response: %s", resultString);

        // If everything went fine, return the JSON document.
        // Otherwise throw an exception.
        if (res.getStatus() == Net::HTTPResponse::HTTP_OK)
        {
            return result;
        }
        else
        {
            throw ApplicationException("Exchangeratelab Error", "");
        }
    }
} // namespace trader
