#include "stdafx.h"
#include "cryptowatch.h"
#include "cryptowatchapi.h"
#include "helper.h"

namespace trader {

    Cryptowatch::Cryptowatch(Poco::AutoPtr<trader::App> _app)
        : api(_app, this)
    {
    }

    Cryptowatch::~Cryptowatch()
    {
    }

    Dynamic::Var Cryptowatch::invoke(const string& httpMethod, URI& uri)
    {
        (void)httpMethod;
        static FastMutex mutex;
        static Stopwatch lockDownStopWatch;
        {
            FastMutex::ScopedLock lock(mutex);
            Clock::ClockDiff elapsedTime = lockDownStopWatch.elapsed();
            if (elapsedTime > 0 && elapsedTime < 60 * 60 * 1000)
            {
                throw TimeoutException("Cryptowatch Error", "API allowance exceeded. Initiate 1 hour lockdown");
            }
            else
            {
                lockDownStopWatch.reset();
                lockDownStopWatch.stop();
            }
        }

        // Create the request URI.
        HTTPSClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);
        session.sendRequest(req);

        Logger::get("Logs").information("Send Request: %s", uri.toString());

        // Receive the response.
        HTTPResponse res;
        istream& rs = session.receiveResponse(res);

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
                return result;
            case HTTPResponse::HTTP_TOO_MANY_REQUESTS:
                {
                    FastMutex::ScopedLock lock(mutex);
                    lockDownStopWatch.start();
                }
                throw TimeoutException("Cryptowatch Error", "API allowance exceeded. Initiate 1 hour lockdown");
            default:
                throw ApplicationException("Cryptowatch Error", "");
        }
    }
}
