#pragma once

#include "endpoint.h"
#include "fileoutputstream.h"
#include "config.h"


namespace trader {

	using Poco::Util::Application;
	using Poco::Util::Option;
	using Poco::Util::OptionSet;
	using Poco::Util::HelpFormatter;
	using Poco::Util::AbstractConfiguration;
	using Poco::Util::OptionCallback;
	using Poco::DirectoryIterator;
	using Poco::File;
	using Poco::Path;
	using namespace Poco;
	using namespace std;

	inline void getAPIName(const string& apiFile, string& apiName)
	{
		Path p(apiFile);
		apiName = p.getBaseName();
	}

	class ScopedNamespace
	{
	public:

		ScopedNamespace(ApiFileOutputStream& stream, string& nameSpace)
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
		ApiFileOutputStream& _stream;
	};

	class ScopedStream
	{
	public:
		enum IndentType
		{
			INC = 0,
			DEC
		};

		ScopedStream(ApiFileOutputStream& stream, bool brackets = true, IndentType indent = INC)
			: _stream(stream)
			, _indent(indent)
			, _brackets(brackets)
		{
			if (brackets) stream << "{" << endl;
			if (indent == INC) ++stream; else --stream;
		}

		~ScopedStream()
		{
			if (_indent == INC) --_stream; else ++_stream;
			if (_brackets) _stream << "}" << endl;
		}

		IndentType _indent;
		ApiFileOutputStream& _stream;
		bool _brackets;
	};

	template<size_t N> class ScopedClass
	{
		array<const char*, N> parentClasses;
	public:
		template <typename ...T,
			typename enable_if<sizeof...(T) == N, int>::type = 0>
		ScopedClass(ApiFileOutputStream& stream, const string& className, T ...args) :
			_className(className),
			_stream(stream),
			parentClasses{args...}
		{
			stream << "class " << className;
			bool first = true;
			for (auto& parentClass : parentClasses)
			{
				if (!first) stream << ", ";
				else stream << " : ";
				stream << " public " << parentClass;
				first = false;
			}
			stream << " {";
			stream << endl;
			++stream;

			//public section 
			{
				ScopedStream scoped(stream, false, ScopedStream::DEC);
				stream << "public:" << endl;
			}
			//declare constructor
			stream << endl;
			stream << "// Constructor" << endl;
			stream << className << "()" << cendl;

			//declare destructor
			stream << endl;
			stream << "// Destructor" << endl;
			stream << "~" << className << "()" << cendl;
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
		ApiFileOutputStream& _stream;
		const string& _className;
	};
	
	inline void startHeader(ApiFileOutputStream& stream, Int32 num, ...)
	{
		stream << "#pragma once " << endl;
		va_list arguments;
		va_start(arguments, num);
		for (UInt32 cnt = 0; cnt < num; cnt++)
		{
			const char* fileName = va_arg(arguments, const char*);
			stream << "#include \"" << fileName << "\"" << endl;
		}
		va_end(arguments);
		stream << endl;
		stream << endl;
	}

	inline void startCpp(ApiFileOutputStream& stream, Int32 num, ...)
	{
		stream << "#include \"stdafx.h\" " << endl;
		va_list arguments;
		va_start(arguments, num);
		for (UInt32 cnt = 0; cnt < num; cnt++)
		{
			const char* fileName = va_arg(arguments, const char*);
			stream << "#include \"" << fileName  << "\"" << endl;
		}
		va_end(arguments);
		stream << endl;
	}

	inline void construct(ApiFileOutputStream& cpp, const string& className, Int32 num, ...)
	{
		cpp << className << "::" << className << "() ";
		{
			ScopedStream scope(cpp);
			va_list arguments;
			va_start(arguments, num);
			poco_assert(num % 2 == 0);
			for (UInt32 cnt = 0; cnt < num; cnt+=2)
			{
				const char* str = va_arg(arguments, const char*);
				cpp << str << " = \"" << va_arg(arguments, const char*) << "\"" << cendl;
			}
			va_end(arguments);
		}
		cpp << endl;
		cpp << className << "::~" << className << "() ";
		{
			ScopedStream scope(cpp);
		}
		cpp << endl;
	}

}
