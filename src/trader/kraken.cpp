#include "stdafx.h"
#include "kraken.h"
#include "api.h"
#include "krakenconfig.h"
#include "krakendatabase.h"
#include "helper.h"
//#include "openssl/hmac.h"
#include "openssl/ssl.h"

namespace trader {

    Kraken::Kraken(AutoPtr<trader::App> _app)
		: api(_app, this)
		, app(_app)
		, dataBase(new KrakenDatabase(_app->dbSession))
		, executeTimer(0, 1000)
	{
	}

	void Kraken::run()
	{
		dataBase->init();
		//dataBase->clear();

		executeTimer.start(TimerCallback<Kraken>(*this, &Kraken::execute));
	}

	void Kraken::execute(Timer& timer)
	{
		static std::atomic_int32_t idx = 0;
        if (serialExecutionList.size())
        {
            serialExecutionList[idx % serialExecutionList.size()](timer);
            ++idx;
        }
	}

    Kraken::~Kraken()
	{
	}

    class SHA512Engine : public SHA2Engine
    {
    public:
        enum
        {
            BLOCK_SIZE = 128,
            DIGEST_SIZE = 512/8
        };
    };

    class SHA256Engine : public SHA2Engine
    {
    public:
        enum
        {
            BLOCK_SIZE = 64,
            DIGEST_SIZE = 256/8
        };

        SHA256Engine(std::string _str)
            : SHA2Engine(SHA_256)
        {
            updateImpl(_str.c_str(), _str.length());
        }

    };

#if defined(POCO_OS_FAMILY_WINDOWS)
    // MSVC defines this in winsock2.h!?
    typedef struct timeval {
        long tv_sec;
        long tv_usec;
    } timeval;

    int gettimeofday(struct timeval * tp, struct timezone * tzp)
    {
        (void)tzp;
        // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
        // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
        // until 00:00:00 January 1, 1970 
        static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

        SYSTEMTIME  system_time;
        FILETIME    file_time;
        uint64_t    time;

        GetSystemTime(&system_time);
        SystemTimeToFileTime(&system_time, &file_time);
        time = ((uint64_t)file_time.dwLowDateTime);
        time += ((uint64_t)file_time.dwHighDateTime) << 32;

        tp->tv_sec = (long)((time - EPOCH) / 10000000L);
        tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
        return 0;
    }
#endif

    std::string create_nonce()
    {
        std::ostringstream oss;

        timeval tp;
        if (gettimeofday(&tp, NULL) != 0) {
            oss << "gettimeofday() failed: " << strerror(errno);
            throw std::runtime_error(oss.str());
        }
        else {
            // format output string 
            oss << std::setfill('0')
                << std::setw(10) << tp.tv_sec
                << std::setw(6) << tp.tv_usec;
        }
        return oss.str();
    }

    std::vector<unsigned char> sha256(const std::string& data)
    {
        std::vector<unsigned char> digest(SHA256_DIGEST_LENGTH);

        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, data.c_str(), data.length());
        SHA256_Final(digest.data(), &ctx);

        return digest;
    }

    //------------------------------------------------------------------------------
    // helper function to decode a base64 string to a vector of bytes:
    std::vector<unsigned char> b64_decode(const std::string& data)
    {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

        BIO* bmem = BIO_new_mem_buf((void*)data.c_str(), (int)data.length());
        bmem = BIO_push(b64, bmem);

        std::vector<unsigned char> output(data.length());
        int decoded_size = BIO_read(bmem, output.data(), (int)output.size());
        BIO_free_all(bmem);

        if (decoded_size < 0)
            throw std::runtime_error("failed while decoding base64.");

        return output;
    }

    //------------------------------------------------------------------------------
    // helper function to encode a vector of bytes to a base64 string:
    std::string b64_encode(const std::vector<unsigned char>& data)
    {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

        BIO* bmem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bmem);

        BIO_write(b64, data.data(), (int)data.size());
        BIO_flush(b64);

        BUF_MEM* bptr = NULL;
        BIO_get_mem_ptr(b64, &bptr);

        std::string output(bptr->data, bptr->length);
        BIO_free_all(b64);

        return output;
    }

    //------------------------------------------------------------------------------
    // helper function to hash with HMAC algorithm:
    std::vector<unsigned char>
        hmac_sha512(const std::vector<unsigned char>& data,
            const std::vector<unsigned char>& key)
    {
        unsigned int len = EVP_MAX_MD_SIZE;
        std::vector<unsigned char> digest(len);

        HMAC_CTX ctx;
        HMAC_CTX_init(&ctx);

        HMAC_Init_ex(&ctx, key.data(), (int)key.size(), EVP_sha512(), NULL);
        HMAC_Update(&ctx, data.data(), data.size());
        HMAC_Final(&ctx, digest.data(), &len);

        HMAC_CTX_cleanup(&ctx);

        return digest;
    }

    std::string signature(const std::string& path,
        const std::string& nonce,
        const std::string& postdata,
        const std::string& secret
        )
    {
        // add path to data to encrypt
        std::vector<unsigned char> data(path.begin(), path.end());

        // concatenate nonce and postdata and compute SHA256
        std::vector<unsigned char> nonce_postdata = sha256(nonce + postdata);

        // concatenate path and nonce_postdata (path + sha256(nonce + postdata))
        data.insert(data.end(), nonce_postdata.begin(), nonce_postdata.end());

        // and compute HMAC
        return b64_encode(hmac_sha512(data, b64_decode(secret)));
    }

	Dynamic::Var Kraken::invoke(const std::string& httpMethod, URI& uri)
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

        //Add timestamp
        string nonce = create_nonce();
        uri.addQueryParameter(string("nonce"), nonce);

		// Create the request URI.
		HTTPSClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPMessage::HTTP_1_1);
		req.add("Accept-Encoding", "gzip");

		// Sign request
		if (httpMethod == HTTPRequest::HTTP_POST)
		{
            //Initialize POST Form with GET params
			HTMLForm form(req);
			form.setEncoding(HTMLForm::ENCODING_URL);

            //Convert Get request to POST
            req.setMethod(HTTPRequest::HTTP_POST);
            req.setURI(uri.getPath());

			//Key
			req.set("API-Key", api.config.dataObject.api_key);

            //Extract POST data
            ostringstream formData;
            form.write(formData);

            req.set("API-Sign", signature(uri.getPath(), nonce, formData.str(), api.config.dataObject.private_key));
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
            Poco::AutoPtr<ErrorIntrospector> errorMsgs = new ErrorIntrospector();
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
}
