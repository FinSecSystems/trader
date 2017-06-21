#pragma once

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

	class ApiFileOutputStream
	{
	public:

		ApiFileOutputStream& operator++()
		{
			indentation++;
			return *this;
		}

		ApiFileOutputStream& operator--()
		{

			poco_assert(indentation > 0);
			indentation--;
			return *this;
		}

		ApiFileOutputStream(const string& path, ios::openmode mode = ios::out | ios::trunc)
			: stream(path, mode)
			, indentation(0)
		{}

		class tabs
		{
			size_t _n;
		public:
			explicit tabs(size_t n) : _n(n) {}
			size_t getn() const { return _n; }
			friend std::ostream& operator<<(ostream& os, const tabs& obj)
			{
				size_t n = obj.getn();
				for (size_t i = 0; i < n; ++i)
					os << "\t";
				return os;
			}
		};

		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const char* text)
		{
			os.tempStream << text;
			return os;
		}

		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, string& str)
		{
			os.tempStream << str;
			return os;
		}

		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const string& str)
		{
			os.tempStream << str;
			return os;
		}

		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, ApiFileOutputStream& (*_Pfn)(ApiFileOutputStream&))
		{
			return ((*_Pfn)(os));
		}

		friend ApiFileOutputStream & endl(ApiFileOutputStream & os)
		{
			os.stream << std::endl;
			os.stream << tabs(os.indentation);
			os.stream << os.tempStream.str();
			os.tempStream.str("");
			os.tempStream.clear();
			return os;
		}

		friend ApiFileOutputStream & cendl(ApiFileOutputStream & os)
		{
			os.stream << std::endl;
			os.stream << tabs(os.indentation);
			os.stream << os.tempStream.str();
			os.stream << ";";
			os.tempStream.str("");
			os.tempStream.clear();
			return os;
		}

		Int32 indentation;
		Poco::FileOutputStream stream;
		ostringstream tempStream;
	};

	class tabs
	{
		size_t _n;
	public:
		explicit tabs(size_t n) : _n(n) {}
		size_t getn() const { return _n; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const tabs& obj)
		{
			size_t n = obj.getn();
			for (size_t i = 0; i < n; ++i)
				os.tempStream << "\t";
			return os;
		}
		friend std::ostringstream& operator<<(std::ostringstream& os, const tabs& obj)
		{
			size_t n = obj.getn();
			for (size_t i = 0; i < n; ++i)
				os << "\t";
			return os;
		}
	};

}

namespace std {
	ostringstream & cendl(ostringstream & os)
	{
		os << std::endl;
		os << ";";
		return os;
	}
}
