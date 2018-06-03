#include "stdafx.h"
#include "cryptowatch.h"
#include "cryptowatchapi.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="cryptowatch.cpp" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Cryptowatch Implementation</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "cryptowatchdatabase.h"
#include "helper.h"

namespace trader
{

    using namespace CryptowatchApi;
    using namespace CryptowatchDatabase;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Gets a connection. </summary>
    ///
    /// <param name="connectionId"> Identifier for the connection. </param>
    ///
    /// <returns> The connection. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AutoPtr< Interface::Connection > Cryptowatch::getConnection(const std::string &connectionId)
    {
        return new CryptowatchConnection(connectionId, new Cryptowatch());
    }

    /// <summary> Initializes a new instance of the Cryptowatch class. </summary>
    Cryptowatch::Cryptowatch()
        : api(AppManager::instance.getApp(), this)
        , dataBase(new CryptowatchDatabase::Tables(DbManager::instance.getDb()->getDbSession()))
    {
        dataBase->init();
    }

    /// <summary> Finalizes an instance of the Cryptowatch class. </summary>
    Cryptowatch::~Cryptowatch() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Executes the given operation on a different thread, and waits for the result. </summary>
    ///
    /// <exception cref="TimeoutException">	    Thrown when a Timeout error condition occurs. </exception>
    /// <exception cref="ApplicationException"> Thrown when an Application error condition occurs. </exception>
    ///
    /// <param name="httpMethod"> The HTTP method. </param>
    /// <param name="uri">		  [in,out] URI of the document. </param>
    ///
    /// <returns> A Dynamic::Var. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Dynamic::Var Cryptowatch::invoke(const string &httpMethod, URI &uri)
    {
        (void)httpMethod;
        static FastMutex mutex;
        static Int32 lockDownHour = -1;
        {
            FastMutex::ScopedLock lock(mutex);
            if (lockDownHour != -1)
            {
                time_point< system_clock > currentTime = system_clock::now();
                system_clock::duration currentDuration = currentTime.time_since_epoch();
                hours h = duration_cast< hours >(currentDuration);
                int32_t newHour = h.count();
                if (lockDownHour == newHour)
                {
                    throw TimeoutException("Cryptowatch Error", "API allowance exceeded. Initiate 1 hour lockdown");
                }
                else
                {
                    lockDownHour = -1;
                }
            }
        }

        // Create the request URI.
        HTTPSClientSession session(uri.getHost(), uri.getPort());
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
        std::string resultString = Dynamic::Var::toString(result);
        Logger::get("Logs").information("Received Response: %s", resultString);

        // If everything went fine, return the JSON document.
        // Otherwise throw an exception.
        switch (res.getStatus())
        {
            case HTTPResponse::HTTP_OK:
            {
                Poco::AutoPtr< AllowanceIntrospector > allowance = new AllowanceIntrospector();
                allowance->read(result);
                if (allowance->dataObject.allowanceObject.isSetRemaining())
                {
                    time_point< system_clock > currentTime = system_clock::now();
                    system_clock::duration currentDuration = currentTime.time_since_epoch();
                    hours h = duration_cast< hours >(currentDuration);

                    Api_Cost::Record recInfo;
                    recInfo.timeStamp = (Int32)time(nullptr);
                    recInfo.method = uri.toString();
                    recInfo.cost = (double)allowance->dataObject.allowanceObject.remaining;
                    dataBase->api_CostTable->insert(recInfo);

                    Logger::get("Logs").information("Cryptowatch: %iL nanoseconds remaining for %i hour",
                                                    allowance->dataObject.allowanceObject.cost, h.count());

                    if (allowance->dataObject.allowanceObject.remaining <= 0)
                    {
                        {
                            FastMutex::ScopedLock lock(mutex);
                            lockDownHour = h.count();
                        }
                    }
                }
                return result;
            }
            case HTTPResponse::HTTP_TOO_MANY_REQUESTS:
            {
                time_point< system_clock > currentTime = system_clock::now();
                system_clock::duration currentDuration = currentTime.time_since_epoch();
                hours h = duration_cast< hours >(currentDuration);
                {
                    FastMutex::ScopedLock lock(mutex);
                    lockDownHour = h.count();
                }
                throw TimeoutException("Cryptowatch Error", "API allowance exceeded. Initiate 1 hour lockdown");
            }
            default:
                throw ApplicationException("Cryptowatch Error", "");
        }
    }
} // namespace trader
