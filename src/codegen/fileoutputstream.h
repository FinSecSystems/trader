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

		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const Int32& num)
		{
			os.tempStream << num;
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

	class ApiStreamBuffer
	{
	public:

		ApiStreamBuffer& operator++()
		{
			indentation++;
			return *this;
		}

		ApiStreamBuffer& operator--()
		{

			poco_assert(indentation > 0);
			indentation--;
			return *this;
		}

		ApiStreamBuffer(ApiFileOutputStream& fileStream)
		{
			indentation = fileStream.indentation;
		}

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

		friend ApiStreamBuffer& operator<<(ApiStreamBuffer& os, const char* text)
		{
			os.tempStream << text;
			return os;
		}

		friend ApiStreamBuffer& operator<<(ApiStreamBuffer& os, string& str)
		{
			os.tempStream << str;
			return os;
		}

		friend ApiStreamBuffer& operator<<(ApiStreamBuffer& os, const string& str)
		{
			os.tempStream << str;
			return os;
		}

		friend ApiStreamBuffer& operator<<(ApiStreamBuffer& os, ApiStreamBuffer& (*_Pfn)(ApiStreamBuffer&))
		{
			return ((*_Pfn)(os));
		}

		friend ApiStreamBuffer & endl(ApiStreamBuffer & os)
		{
			os.tempStream << std::endl;
			os.tempStream << tabs(os.indentation);
			return os;
		}

		friend ApiStreamBuffer & cendl(ApiStreamBuffer & os)
		{
			os.tempStream << ";";
			os.tempStream << std::endl;
			os.tempStream << tabs(os.indentation);
			return os;
		}

		std::string str()
		{
			return tempStream.str();
		}

		Int32 indentation;
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
		friend ApiStreamBuffer& operator<<(ApiStreamBuffer& os, const tabs& obj)
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

	class var_name
	{
		std::string& _str;
	public:
		explicit var_name(std::string& str) : _str(str) {}
		string& getstr() const { return _str; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const var_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
				std::transform(newStr.begin(), newStr.begin()+1, newStr.begin(), ::tolower);
			os.tempStream << newStr;
			return os;
		}
	};

	class type_name
	{
		std::string& _str;
	public:
		explicit type_name(std::string& str) : _str(str) {}
		string& getstr() const { return _str; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const type_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::toupper);
			os.tempStream << newStr;
			return os;
		}
	};

}

namespace std {
	inline ostringstream & cendl(ostringstream & os)
	{
		os << std::endl;
		os << ";";
		return os;
	}
}
