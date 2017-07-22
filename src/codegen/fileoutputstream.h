#pragma once

namespace std {
	inline ostringstream & cendl(ostringstream & os)
	{
		os << std::endl;
		os << ";";
		return os;
	}
	inline std::ostringstream & dot(std::ostringstream & os)
	{
		if (os.str().length())
		{
			os << ".";
		}
		return os;
	}

	inline  std::ostringstream& operator<<(std::ostringstream& os, std::ostringstream& (*_Pfn)(std::ostringstream&))
	{
		return ((*_Pfn)(os));
	}
}

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

		inline ApiStreamBuffer & dot(ApiStreamBuffer & os)
		{
			os.tempStream << ".";
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


	class temp_name
	{
		size_t _n;
	public:
		explicit temp_name(size_t n) : _n(n) {}
		size_t getn() const { return _n; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const temp_name& obj)
		{
			os.tempStream << "obj" << obj.getn();
			return os;
		}
		friend std::ostringstream& operator<<(std::ostringstream& os, const temp_name& obj)
		{
			os << "obj" << obj.getn();
			return os;
		}

	};

	class clean_name
	{
		std::string _str;
	public:
		explicit clean_name(std::string& str) : _str(str) {}
		explicit clean_name(const char* str) : _str(str) {}
		string getstr() const { return _str; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const clean_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
			}
			os.tempStream << newStr;
			return os;
		}
		friend std::ostringstream& operator<<(std::ostringstream& os, const clean_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
			}
			os << newStr;
			return os;
		}
		template<class _Traits> friend
			basic_ostream<char, _Traits>& operator<<(
				basic_ostream<char, _Traits>& _Ostr,
				const clean_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
			}
			_Ostr << newStr;
			return _Ostr;
		}
	};

	class var_name
	{
		std::string _str;
	public:
		explicit var_name(std::string& str) : _str(str) {}
		explicit var_name(const std::string& str) : _str(str) {}
		explicit var_name(const char* str) : _str(str) {}
		string getstr() const { return _str; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const var_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::tolower);
			}
			os.tempStream << newStr;
			return os;
		}
		friend std::ostringstream& operator<<(std::ostringstream& os, const var_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::tolower);
			}
			os << newStr;
			return os;
		}
		template<class _Traits> friend
			basic_ostream<char, _Traits>& operator<<(
				basic_ostream<char, _Traits>& _Ostr,
				const var_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::tolower);
			}
			_Ostr << newStr;
			return _Ostr;
		}
	};

	class type_name
 	{
		std::string _str;
	public:
		explicit type_name(std::string& str) : _str(str) {}
		explicit type_name(const std::string& str) : _str(str) {}
		explicit type_name(const char* str) : _str(str) {}
		string getstr() const { return _str; }
		friend ApiFileOutputStream& operator<<(ApiFileOutputStream& os, const type_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				if (!os.tempStream.str().length())
					newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::toupper);
			}
			os.tempStream << newStr;
			return os;
		}
		friend std::ostringstream& operator<<(std::ostringstream& os, const type_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				if (!os.str().length())
					newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::toupper);
			}
			os << newStr;
			return os;
		}
		template<class _Traits> friend
			basic_ostream<char, _Traits>& operator<<(
				basic_ostream<char, _Traits>& _Ostr,
				const type_name& obj)
		{
			string newStr = obj.getstr();
			if (newStr.length())
			{
				if (!_Ostr.width())
					newStr.erase(std::remove(newStr.begin(), newStr.end(), ':'), newStr.end());
				std::transform(newStr.begin(), newStr.begin() + 1, newStr.begin(), ::toupper);
			}
			_Ostr << newStr;
			return _Ostr;
		}
	};


	class expansionstringstream
	{
	public:

		enum Type
		{
			ARRAY = 0,
			OBJECT,
			NUM_TYPES
		};

		expansionstringstream() {}

		expansionstringstream(const expansionstringstream& other)
		{
			varNameStream << other.varNameStream.str();
			typeNameStream << other.typeNameStream.str();
			prefixStream << other.prefixStream.str();
			typeStack = other.typeStack;
		}

		const char* getTypeString(Type type)
		{
			static const char* TypeString[] =
			{
				"Array",
				"Object"
			};
			return TypeString[(Int32)type];
		}

		void updateStack(const char* text)
		{
			string str(text);
			for (UInt32 typeIdx = 0; typeIdx < NUM_TYPES; typeIdx++)
			{
				const char* testString = getTypeString((Type)typeIdx);
				std::size_t found = str.find(testString);
				if (found != std::string::npos)
				{
					typeStack.push_back((Type)typeIdx);
					break;
				}
			}
		}

		friend expansionstringstream& operator<<(expansionstringstream& os, const char* text)
		{
			bool previousWasArray = os.wasPrevious(expansionstringstream::ARRAY);
			os.updateStack(text);
			bool newIsObject = os.wasPrevious(expansionstringstream::OBJECT);
			if (!previousWasArray || !newIsObject)
			{
				if (!os.varNameStream.str().length())
				{
					os.varNameStream << var_name(text);
				}
				else
				{
					os.varNameStream << clean_name(text);
				}
				if (!os.typeNameStream.str().length())
				{
					os.typeNameStream << type_name(text);
				}
				else
				{
					os.typeNameStream << text;
				}
				if (!os.prefixStream.str().length())
				{
					os.prefixStream << var_name(text);
				}
				else
				{
					os.prefixStream << std::dot << var_name(text);
				}
			}
			return os;
		}

		friend expansionstringstream & dot(expansionstringstream & os)
		{
			if (os.prefixStream.str().length())
			{
				os.prefixStream << ".";
			}
			return os;
		}

		friend expansionstringstream& operator<<(expansionstringstream& os, string& str)
		{
			os << str.c_str();
			return os;
		}

		friend expansionstringstream& operator<<(expansionstringstream& os, const string& str)
		{
			os << str.c_str();
			return os;
		}

		friend expansionstringstream& operator<<(expansionstringstream& os, expansionstringstream::Type type)
		{
			os << os.getTypeString(type);
			return os;
		}

		friend expansionstringstream& operator<<(expansionstringstream& os, expansionstringstream& (*_Pfn)(expansionstringstream&))
		{
			return ((*_Pfn)(os));
		}

		std::string prefix_str()
		{
			return prefixStream.str();
		}

		std::string var_name_str()
		{
			return varNameStream.str();
		}

		std::string type_name_str()
		{
			return typeNameStream.str();
		}

		bool wasPrevious(Type type)
		{
			if (typeStack.size())
			{
				auto& lastType = typeStack.back();
				return (lastType == type ? true : false);
			}
			return false;
		}

		bool has(Type type)
		{
			std::vector<Type>::iterator it = find(typeStack.begin(), typeStack.end(), type);
			return (it != typeStack.end() ? true : false);
		}

		ostringstream varNameStream;
		ostringstream typeNameStream;
		ostringstream prefixStream;
		vector<Type>   typeStack;
	};

}

