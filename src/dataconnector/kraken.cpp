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

    AutoPtr< Interface::Connection > Kraken::getConnection(const std::string &connectionId)
    {
        return new KrakenConnection(connectionId, new Kraken());
    }

    Kraken::Kraken()
        : api(AppManager::instance.get()->getApp(), this)
        , executeTimer(0, 1000)
        , dataBase(new KrakenDatabase::Tables(DbManager::instance.getDb()->getDbSession()))
    {
    }

    void Kraken::run()
    {
        dataBase->init();
        // dataBase->clear();

        executeTimer.start(TimerCallback< Kraken >(*this, &Kraken::execute));
    }

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

    Kraken::~Kraken() {}

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
