#include "stdafx.h"
#include "bittrex.h"
#include "bittrexapi.h"
#include "helper.h"

namespace trader {

    using namespace BittrexApi;

    Bittrex::Bittrex(Poco::AutoPtr<trader::App> _app)
        : api(_app, this)
    {
    }

    Bittrex::~Bittrex()
    {
    }

    Dynamic::Var Bittrex::invoke(const string& httpMethod, URI& uri)
    {
        (void)httpMethod;

        // Create the request URI.
        HTTPSClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);
        //req.add("Accept-Encoding", "gzip");

        // Sign request
        if (httpMethod == HTTPRequest::HTTP_POST)
        {
            //TODO

            //Convert to POST
            HTMLForm form(req);
            req.setMethod(HTTPRequest::HTTP_POST);
            req.setURI(uri.getPath());
            form.setEncoding(HTMLForm::ENCODING_URL);

            //Submit
            form.prepareSubmit(req);
            ostream& ostr = session.sendRequest(req);
            form.write(ostr);
        }
        else
        {
            session.sendRequest(req);
        }

        Logger::get("Logs").information("Send Request: %s", uri.toString());

        // Receive the response.
        HTTPResponse res;
        istream& rs = session.receiveResponse(res);

        //InflatingInputStream inflater(rs, InflatingStreamBuf::STREAM_GZIP);
        // Parse the JSON
        JSON::Parser parser;
        //parser.parse(inflater);
        parser.parse(rs);
        Dynamic::Var result = parser.result();
        string resultString = Dynamic::Var::toString(result);
        Logger::get("Logs").information("Received Response: %s", resultString);

        // If everything went fine, return the JSON document.
        // Otherwise throw an exception.
        if (res.getStatus() == HTTPResponse::HTTP_OK)
        {
            Poco::AutoPtr<ResultIntrospector> msg = new ResultIntrospector();
            msg->read(result);
            if (!msg->dataObject.success)
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
}
