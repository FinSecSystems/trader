#pragma once

#include "openssl/ssl.h"

namespace trader
{

    class SHA512Engine : public SHA2Engine
    {
      public:
        enum
        {
            BLOCK_SIZE = 128,
            DIGEST_SIZE = 512 / 8
        };
    };

    class SHA256Engine : public SHA2Engine
    {
      public:
        enum
        {
            BLOCK_SIZE = 64,
            DIGEST_SIZE = 256 / 8
        };

        SHA256Engine(std::string _str)
            : SHA2Engine(SHA_256)
        {
            updateImpl(_str.c_str(), _str.length());
        }
    };

#if defined(POCO_OS_FAMILY_WINDOWS)
    // MSVC defines this in winsock2.h!?
    typedef struct timeval
    {
        long tv_sec;
        long tv_usec;
    } timeval;

    inline int gettimeofday(struct timeval *tp, struct timezone *tzp)
    {
        (void)tzp;
        // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
        // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
        // until 00:00:00 January 1, 1970
        static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

        SYSTEMTIME system_time;
        FILETIME file_time;
        uint64_t time;

        GetSystemTime(&system_time);
        SystemTimeToFileTime(&system_time, &file_time);
        time = ((uint64_t)file_time.dwLowDateTime);
        time += ((uint64_t)file_time.dwHighDateTime) << 32;

        tp->tv_sec = (long)((time - EPOCH) / 10000000L);
        tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
        return 0;
    }
#endif

    inline std::string create_nonce()
    {
        std::ostringstream oss;

        timeval tp;
        if (gettimeofday(&tp, NULL) != 0)
        {
            oss << "gettimeofday() failed: " << strerror(errno);
            throw std::runtime_error(oss.str());
        }
        else
        {
            // format output string
            oss << std::setfill('0') << std::setw(10) << tp.tv_sec << std::setw(6) << tp.tv_usec;
        }
        return oss.str();
    }

    inline std::vector< unsigned char > sha256(const std::string &data)
    {
        std::vector< unsigned char > digest(SHA256_DIGEST_LENGTH);

        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, data.c_str(), data.length());
        SHA256_Final(digest.data(), &ctx);

        return digest;
    }

    //------------------------------------------------------------------------------
    // helper function to decode a base64 string to a vector of bytes:
    inline std::vector< unsigned char > b64_decode(const std::string &data)
    {
        BIO *b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

        BIO *bmem = BIO_new_mem_buf((void *)data.c_str(), (int)data.length());
        bmem = BIO_push(b64, bmem);

        std::vector< unsigned char > output(data.length());
        int decoded_size = BIO_read(bmem, output.data(), (int)output.size());
        BIO_free_all(bmem);

        if (decoded_size < 0)
            throw std::runtime_error("failed while decoding base64.");

        return output;
    }

    //------------------------------------------------------------------------------
    // helper function to encode a vector of bytes to a base64 string:
    inline std::string b64_encode(const std::vector< unsigned char > &data)
    {
        BIO *b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

        BIO *bmem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bmem);

        BIO_write(b64, data.data(), (int)data.size());
        BIO_flush(b64);

        BUF_MEM *bptr = NULL;
        BIO_get_mem_ptr(b64, &bptr);

        std::string output(bptr->data, bptr->length);
        BIO_free_all(b64);

        return output;
    }

    //------------------------------------------------------------------------------
    // helper function to hash with HMAC algorithm:
    inline std::vector< unsigned char > hmac_sha512(const std::vector< unsigned char > &data,
                                                    const std::vector< unsigned char > &key)
    {
        unsigned int len = EVP_MAX_MD_SIZE;
        std::vector< unsigned char > digest(len);

        HMAC_CTX ctx;
        HMAC_CTX_init(&ctx);

        HMAC_Init_ex(&ctx, key.data(), (int)key.size(), EVP_sha512(), NULL);
        HMAC_Update(&ctx, data.data(), data.size());
        HMAC_Final(&ctx, digest.data(), &len);

        HMAC_CTX_cleanup(&ctx);

        return digest;
    }

} // namespace trader
