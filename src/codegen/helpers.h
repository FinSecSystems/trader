#pragma once

#include "config.h"
#include "endpoint.h"
#include "fileoutputstream.h"

namespace trader
{

    using Poco::DirectoryIterator;
    using Poco::File;
    using Poco::Path;
    using Poco::Util::AbstractConfiguration;
    using Poco::Util::Application;
    using Poco::Util::HelpFormatter;
    using Poco::Util::Option;
    using Poco::Util::OptionCallback;
    using Poco::Util::OptionSet;
    using namespace Poco;
    using namespace std;

    inline void getAPIName(string name, const string &apiFile, string &apiName)
    {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.length())
            std::transform(name.begin(), name.begin() + 1, name.begin(), ::toupper);
        Path p(apiFile);
        string fileName = p.getBaseName();
        std::string::size_type pos = fileName.find('.');
        if (pos != std::string::npos)
            apiName = fileName.substr(0, pos) + name;
        else
            apiName = fileName + name;
        std::transform(apiName.begin(), apiName.begin() + 1, apiName.begin(), ::toupper);
    }

    class ScopedNamespace
    {
      public:
        ScopedNamespace(ApiFileOutputStream &stream, string &nameSpace)
            : _nameSpace(nameSpace)
            , _stream(stream)
        {
            if (!_nameSpace.empty())
            {
                stream << "namespace " << _nameSpace << " {" << endl;
                stream << endl;
                ++stream;
            }
        }

        ~ScopedNamespace()
        {
            if (!_nameSpace.empty())
            {
                --_stream;
                _stream << "} //" << _nameSpace << endl;
            }
        }

      private:
        string _nameSpace;
        ApiFileOutputStream &_stream;
    };

    template < class StreamType = ApiFileOutputStream > class ScopedStream
    {
      public:
        enum IndentType
        {
            INC = 0,
            DEC
        };

        ScopedStream(StreamType &stream, bool brackets = true, IndentType indent = INC)
            : _indent(indent)
            , _stream(stream)
            , _brackets(brackets)
        {
            if (brackets)
                stream << "{" << endl;
            if (indent == INC)
                ++stream;
            else
                --stream;
        }

        ~ScopedStream()
        {
            if (_indent == INC)
                --_stream;
            else
                ++_stream;
            if (_brackets)
                _stream << "}" << endl;
        }

        IndentType _indent;
        StreamType &_stream;
        bool _brackets;
    };

    template < size_t N, class StreamType = ApiFileOutputStream > class ScopedClass
    {
        array< const char *, N > parentClasses;

      public:
        template < typename... T, typename enable_if< sizeof...(T) == N, int >::type = 0 >
        ScopedClass(StreamType &stream, const string &className, T... args)
            : parentClasses{{args}...}
            , _stream(stream)
            , _className(className)
        {
            stream << "class " << className;
            bool first = true;
            for (auto &parentClass : parentClasses)
            {
                if (!first)
                    stream << ", ";
                else
                    stream << " : ";
                stream << " public " << parentClass;
                first = false;
            }
            stream << " {";
            stream << endl;
            ++stream;

            // public section
            {
                ScopedStream< StreamType > scoped(stream, false, ScopedStream< StreamType >::DEC);
                stream << "public:" << endl;
            }

            stream << endl;
        }

        ~ScopedClass()
        {
            if (!_className.empty())
            {
                --_stream;
                _stream << "}; //" << _className << endl;
                _stream << endl;
            }
        }

      private:
        StreamType &_stream;
        string _className;
    };

    template < size_t N, class StreamType = ApiFileOutputStream > class ScopedStruct
    {
        array< const char *, N > parentClasses;

      public:
        template < typename... T, typename enable_if< sizeof...(T) == N, int >::type = 0 >
        ScopedStruct(StreamType &stream, const string &className, T... args)
            : parentClasses{args...}
            , _stream(stream)
            , _className(className)
        {
            stream << "struct " << className;
            bool first = true;
            for (auto &parentClass : parentClasses)
            {
                if (!first)
                    stream << ", ";
                else
                    stream << " : ";
                stream << " public " << parentClass;
                first = false;
            }
            stream << " {";
            stream << endl;
            ++stream;
            stream << endl;
        }

        ~ScopedStruct()
        {
            if (!_className.empty())
            {
                --_stream;
                _stream << trader::endl;
                _stream << "}" << trader::cendl;
                _stream << trader::endl;
            }
        }

      private:
        StreamType &_stream;
        string _className;
    };

    inline void startHeader(ApiFileOutputStream &stream, Int32 num, ...)
    {
        stream << "#pragma once " << endl;
        va_list arguments;
        va_start(arguments, num);
        for (Int32 cnt = 0; cnt < num; cnt++)
        {
            const char *fileName = va_arg(arguments, const char *);
            stream << "#include \"" << fileName << "\"" << endl;
        }
        va_end(arguments);
        stream << endl;
        stream << endl;
    }

    inline void startCpp(ApiFileOutputStream &stream, Int32 num, ...)
    {
        stream << "#include \"stdafx.h\" " << endl;
        va_list arguments;
        va_start(arguments, num);
        for (Int32 cnt = 0; cnt < num; cnt++)
        {
            const char *fileName = va_arg(arguments, const char *);
            stream << "#include \"" << fileName << "\"" << endl;
        }
        va_end(arguments);
        stream << endl;
    }

    inline void construct(ApiFileOutputStream &cpp, const string &className, Int32 num, ...)
    {
        cpp << className << "::" << className << "() ";
        {
            ScopedStream< ApiFileOutputStream > scope(cpp);
            va_list arguments;
            va_start(arguments, num);
            poco_assert(num % 2 == 0);
            for (Int32 cnt = 0; cnt < num; cnt += 2)
            {
                const char *str = va_arg(arguments, const char *);
                cpp << str << " = \"" << va_arg(arguments, const char *) << "\"" << cendl;
            }
            va_end(arguments);
        }
        cpp << endl;
        cpp << className << "::~" << className << "() ";
        {
            ScopedStream< ApiFileOutputStream > scope(cpp);
        }
        cpp << endl;
    }

    inline void construct_header(ApiFileOutputStream &stream, const string &className, Int32 num, ...)
    {
        stream << className << "(";
        va_list arguments;
        va_start(arguments, num);
        poco_assert(num % 2 == 0);
        for (Int32 cnt = 0; cnt < num; cnt += 2)
        {
            if (cnt > 0)
                stream << ", ";
            const char *str = va_arg(arguments, const char *);
            stream << str << " " << va_arg(arguments, const char *);
        }
        stream << ")" << cendl;
        va_end(arguments);
        stream << endl;
        stream << "~" << className << "()" << cendl;
        stream << endl;
    }

    inline void construct_ex(ApiFileOutputStream &cpp, const string &className, Int32 numParams, Int32 numInitializer,
                             Int32 numStatements, ...)
    {
        cpp << className << "::" << className << "(";
        va_list arguments;
        va_start(arguments, numStatements);
        poco_assert(numParams % 2 == 0);
        for (Int32 cnt = 0; cnt < numParams; cnt += 2)
        {
            if (cnt > 0)
                cpp << ", ";
            const char *str = va_arg(arguments, const char *);
            cpp << str << " " << va_arg(arguments, const char *);
        }
        cpp << ") ";
        {
            ScopedStream< ApiFileOutputStream > scope(cpp);
            poco_assert(numInitializer % 2 == 0);
            for (Int32 cnt = 0; cnt < numInitializer; cnt += 2)
            {
                const char *str = va_arg(arguments, const char *);
                cpp << str << " = " << va_arg(arguments, const char *) << trader::cendl;
            }
            for (Int32 cnt = 0; cnt < numStatements; cnt++)
            {
                cpp << va_arg(arguments, const char *) << trader::endl;
            }
        }
        va_end(arguments);
        cpp << endl;
        cpp << className << "::~" << className << "() ";
        {
            ScopedStream< ApiFileOutputStream > scope(cpp);
        }
        cpp << endl;
    }

    inline std::string &replace(std::string &str, const char *from, const char *to)
    {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, strlen(from), to);
            start_pos += strlen(to); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }
} // namespace trader

#ifdef _DEBUG
#define CODEGEN_DEBUG(x) x
#else
#define CODEGEN_DEBUG(x)
#endif
