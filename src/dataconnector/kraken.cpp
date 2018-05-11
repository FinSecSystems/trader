///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="kraken.cpp" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>Kraken connection implementation</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kraken.h"
#include "api.h"
#include "helper.h"
#include "krakenconfig.h"
#include "krakendatabase.h"
#include "shautils.h"

namespace trader
{

    using namespace KrakenApi;
    using namespace KrakenDatabase;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Gets a connection. </summary>
    ///
    /// <param name="connectionId"> Identifier for the connection. </param>
    ///
    /// <returns> The connection. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AutoPtr< Interface::Connection > Kraken::getConnection(const std::string &connectionId)
    {
        return new KrakenConnection(connectionId, new Kraken());
    }

    /// <summary> Initializes a new instance of the Kraken class. </summary>
    Kraken::Kraken()
        : api(AppManager::instance.getApp(), this)
        , executeTimer(0, 1000)
        , dataBase(new KrakenDatabase::Tables(DbManager::instance.getDb()->getDbSession()))
    {
    }

    /// <summary> Runs this object. </summary>
    void Kraken::run()
    {
        dataBase->init();
        // dataBase->clear();

        executeTimer.start(TimerCallback< Kraken >(*this, &Kraken::execute));
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Executes the given timer. </summary>
    ///
    /// <param name="timer"> [in,out] The timer. </param>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Kraken::execute(Timer &timer)
    {
        static std::atomic< std::int32_t > idx;
        idx = 0;
        if (serialExecutionList.size())
        {
            serialExecutionList[idx % serialExecutionList.size()](timer);
            ++idx;
        }
    }

    /// <summary> Finalizes an instance of the Kraken class. </summary>
    Kraken::~Kraken() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary> Signatures the given file. </summary>
    ///
    /// <param name="path">	    Full pathname of the file. </param>
    /// <param name="nonce">    The nonce. </param>
    /// <param name="postdata"> The postdata. </param>
    /// <param name="secret">   The secret. </param>
    ///
    /// <returns> A std::string. </returns>
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string signature(const std::string &path, const std::string &nonce, const std::string &postdata,
                          const std::string &secret)
    {
        // add path to data to encrypt
        std::vector< unsigned char > data(path.begin(), path.end());

        // concatenate nonce and postdata and compute SHA256
        std::vector< unsigned char > nonce_postdata = sha256(nonce + postdata);

        // concatenate path and nonce_postdata (path + sha256(nonce + postdata))
        data.insert(data.end(), nonce_postdata.begin(), nonce_postdata.end());

        // and compute HMAC
        return b64_encode(hmac_sha512(data, b64_decode(secret)));
    }

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
    Dynamic::Var Kraken::invoke(const std::string &httpMethod, URI &uri)
    {
        static FastMutex lock;
        static time_t lastTimeStamp = 0;
        time_t currentTimeStamp;
        if (lock.tryLock())
        {
            currentTimeStamp = std::time(nullptr);
            if (lastTimeStamp == currentTimeStamp)
            {
                throw TimeoutException("Kraken Error : API executed too fast", "");
            }
            lastTimeStamp = currentTimeStamp;
            lock.unlock();
        }
        else
        {
            throw TimeoutException("Kraken Error : API executed too fast", "");
        }

        // Add timestamp
        string nonce = create_nonce();
        uri.addQueryParameter(string("nonce"), nonce);

        // Create the request URI.
        HTTPSClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);
        req.add("Accept-Encoding", "gzip");

        // Sign request
        if (httpMethod == HTTPRequest::HTTP_POST)
        {
            // Initialize POST Form with GET params
            HTMLForm form(req);
            form.setEncoding(HTMLForm::ENCODING_URL);

            // Convert Get request to POST
            req.setMethod(HTTPRequest::HTTP_POST);
            req.setURI(uri.getPath());

            // Key
            req.set("API-Key", api.config.dataObject.api_key);

            // Extract POST data
            ostringstream formData;
            form.write(formData);

            req.set("API-Sign", signature(uri.getPath(), nonce, formData.str(), api.config.dataObject.private_key));
            // Submit
            form.prepareSubmit(req);
            ostream &ostr = session.sendRequest(req);
            form.write(ostr);
        }
        else
        {
            session.sendRequest(req);
        }

        Logger::get("Logs").information("Send Request: %s", uri.toString());

        // Receive the response.
        HTTPResponse res;
        istream &rs = session.receiveResponse(res);

        InflatingInputStream inflater(rs, InflatingStreamBuf::STREAM_GZIP);
        // Parse the JSON
        JSON::Parser parser;
        parser.parse(inflater);
        Dynamic::Var result = parser.result();
        string resultString = Dynamic::Var::toString(result);
        Logger::get("Logs").information("Received Response: %s", resultString);

        // If everything went fine, return the JSON document.
        // Otherwise throw an exception.
        if (res.getStatus() == HTTPResponse::HTTP_OK)
        {
            Poco::AutoPtr< ErrorIntrospector > errorMsgs = new ErrorIntrospector();
            errorMsgs->read(result);
            if (errorMsgs->dataObject.error.size())
            {
                throw ApplicationException("Kraken Error", "Received Error Response");
            }
            return result;
        }
        else
        {
            throw ApplicationException("Kraken Error", "");
        }
    }
} // namespace trader
