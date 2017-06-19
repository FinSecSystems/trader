#include "stdafx.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/StringTokenizer.h"
#include <iostream>
#include <iomanip>
#include <sstream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Path;


class CodeGenApp : public Application
{
public:
    CodeGenApp()
    {
    }

protected:
    void defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h", "Display help information on command line arguments.")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleHelp)));

        options.addOption(
            Option("outputdir", "o", "Location to write cpp and header files")
            .required(false)
            .repeatable(false)
            .argument("output directory")
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleOutputDir)));

        options.addOption(
            Option("inputdir", "i", "Location of the API JSON files")
            .required(false)
            .repeatable(false)
            .argument("input directory")
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleInputDir)));

        options.addOption(
            Option("namespace", "n", "Namespace")
            .required(false)
            .repeatable(false)
            .argument("input directory")
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleNamespace)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        displayHelp();
        stopOptionsProcessing();
    }

    void handleInputDir(const std::string& name, const std::string& value)
    {
        _inputDir = value;
    }

    void handleOutputDir(const std::string& name, const std::string& value)
    {
        _outputDir = value;
    }

    void handleNamespace(const std::string& name, const std::string& value)
    {
        _namespace = value;
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A simple command line client for posting status updates.");
        helpFormatter.format(std::cout);
    }

	class FileOutputStream;

	class tabs 
	{
		std::size_t _n;
	public:
		explicit tabs(std::size_t n) : _n(n) {}
		std::size_t getn() const { return _n; }
		friend FileOutputStream& operator<<(FileOutputStream& os, const tabs& obj)
		{
			std::size_t n = obj.getn();
			for (std::size_t i = 0; i < n; ++i)
				os.tempStream << "    ";
			return os;
		}
	};

	void newLine(FileOutputStream& stream)
	{
		stream << endl;
	}

    class FileOutputStream
    {
    public:

        FileOutputStream& operator++()
        {
            // actual increment takes place here
            indentation++;
            return *this;
        }

        FileOutputStream& operator--()
        {
            // actual increment takes place here
			poco_assert(indentation > 0);
            indentation--;
            return *this;
        }

        FileOutputStream(const std::string& path, std::ios::openmode mode = std::ios::out | std::ios::trunc)
            : stream(path, mode)
            ,indentation(0)
        {}

        class tabs 
        {
            std::size_t _n;
        public:
            explicit tabs(std::size_t n) : _n(n) {}
            std::size_t getn() const { return _n; }
            friend std::ostream& operator<<(std::ostream& os, const tabs& obj)
            {
                std::size_t n = obj.getn();
                for (std::size_t i = 0; i < n; ++i)
                    os << "    ";
                return os;
            }
        };

        friend FileOutputStream& operator<<(FileOutputStream& os, const char* text)
        {
            os.tempStream << text;
            return os;
        }

        friend FileOutputStream& operator<<(FileOutputStream& os, std::string& str)
        {
            os.tempStream << str;
            return os;
        }

		friend FileOutputStream& operator<<(FileOutputStream& os, const std::string& str)
		{
			os.tempStream << str;
			return os;
		}

        friend FileOutputStream& operator<<(FileOutputStream& os, FileOutputStream& (*_Pfn)(FileOutputStream&))
        {// call basic_ostream manipulator
            return ((*_Pfn)(os));
        }

        friend FileOutputStream & endl(FileOutputStream & os)
        {
            os.stream << std::endl;
            os.stream << tabs(os.indentation);
            os.stream << os.tempStream.str();
            os.tempStream.str("");
            os.tempStream.clear();
            return os;
        }

		friend FileOutputStream & cendl(FileOutputStream & os)
		{
			os.stream << std::endl;
			os.stream << tabs(os.indentation);
			os.stream << os.tempStream.str();
			os.stream << ";";
			os.tempStream.str("");
			os.tempStream.clear();
			return os;
		}

        Poco::Int32 indentation;
        Poco::FileOutputStream stream;
        std::ostringstream tempStream;
    };

	struct Config
	{
		void read(Poco::SharedPtr<Poco::JSON::Object> obj)
		{
			baseUrl = obj->getValue<std::string>("baseurl");
		}

		std::string baseUrl;
	};

	struct ObjectSchemaDefinition
	{
		void read(Poco::SharedPtr<Poco::JSON::Object> obj)
		{
			rootObj = obj;
		}

		void writeCpp(FileOutputStream& cpp)
		{
			cpp << "void " << name << "::read(Poco::JSON::Object::Ptr val) ";
			{
				scopedStream stream(cpp);
				std::vector<std::string> propertyNames;
				rootObj->getNames(propertyNames);
				for (auto& propertyName : propertyNames)
				{
					Poco::JSON::Object::Ptr propertyVal = rootObj->getObject(propertyName);
					std::string type = propertyVal->get("type");
					const char* cppType = getCppType(type);
					if (cppType)
					{
						cpp << propertyName << " = val->getValue<" << cppType << ">(\"" << propertyName << "\")" << cendl;
					}
					else if (isArray(type))
					{
						Poco::JSON::Object::Ptr items = propertyVal->getObject("items");
						std::string type = items->get("type");
						const char* cppType = getCppType(type);
						if (cppType)
						{
							cpp << "Poco::JSON::Array::Ptr " << propertyName << "Array = val->getArray(\"" << propertyName << "\")" << cendl;
							cpp << "for (Poco::UInt32 idx = 0; idx < " << propertyName << "Array->size(); ++idx)" << endl;
							{
								scopedStream stream(cpp);
								cpp << propertyName << ".push_back(" << propertyName << "Array->getElement<" << cppType << ">(idx))" << cendl;
							}
						}
						else if (isArray(type))
						{
							Poco::JSON::Object::Ptr innerItems = items->getObject("items");
							std::string type = innerItems->get("type");
							const char* cppType = getCppType(type);
							cpp << "Poco::JSON::Array::Ptr " << propertyName << "Array = val->getArray(\"" << propertyName << "\")" << cendl;
							cpp << "for (Poco::UInt32 idx = 0; idx < " << propertyName << "Array->size(); ++idx)" << endl;
							{
								scopedStream stream(cpp);
								cpp << "Poco::JSON::Array::Ptr inner" << propertyName << "Array = "<< propertyName << "Array->getArray(idx)" << cendl;
								cpp << "std::vector<" << cppType << "> inner" << propertyName << cendl;
								cpp << "for (Poco::UInt32 innerIdx = 0; innerIdx < inner" << propertyName << "Array->size(); ++innerIdx)" << endl;
								{
									scopedStream stream(cpp);
									cpp << "inner" << propertyName << ".push_back(inner" << propertyName << "Array->getElement<" << cppType << ">(innerIdx))" << cendl;
								}
								cpp << propertyName << ".push_back(inner" << propertyName << ")" << cendl;							}
						}
					}
				}
			}
			cpp << endl;
		}

		const char* getCppType(const std::string& jsonType)
		{
			if (jsonType.compare("double") == 0)
			{
				return "double";
			}
			else if (jsonType.compare("int") == 0)
			{
				return "Poco::Int32";
			}
			return nullptr;
		}

		bool isArray(const std::string& jsonType)
		{
			if (jsonType.compare("array") == 0)
			{
				return true;
			}
			return false;
		}

		void writeHeader(FileOutputStream& header)
		{
			header << "void read(Poco::JSON::Object::Ptr val)" << cendl;

			std::vector<std::string> propertyNames;
			rootObj->getNames(propertyNames);
			for (auto& it : propertyNames)
			{
				Poco::JSON::Object::Ptr propertyVal = rootObj->getObject(it);
				std::string type = propertyVal->get("type");
				const char* cppType = getCppType(type);
				if (cppType)
				{
					header << cppType << tabs(1) << it << cendl;
				}
				else if (isArray(type))
				{
					Poco::JSON::Object::Ptr items = propertyVal->getObject("items");
					std::string type = items->get("type");
					const char* cppType = getCppType(type);
					if (cppType)
					{
						header << "std::vector<" << cppType << "> " << tabs(1) << it << cendl;
					}
					else if (isArray(type))
					{
						Poco::JSON::Object::Ptr innerItems = items->getObject("items");
						std::string type = innerItems->get("type");
						const char* cppType = getCppType(type);
						header << "std::vector<std::vector<" << cppType << ">> " << tabs(1) << it << cendl;
					}
				}
			}
		}

		std::string name;
		Poco::SharedPtr<Poco::JSON::Object> rootObj;
	};

	struct EndPoint
	{
		enum Method {
			POST,
			GET
		};
		std::string url;
		Method method;
		std::string description;
		std::string name;
		std::string responseSchemaName;

		void read(Poco::SharedPtr<Poco::JSON::Object> obj)
		{
			name = obj->getValue<std::string>("title");
			description = obj->getValue<std::string>("description");
			Poco::JSON::Object::Ptr targetSchema = obj->getObject("targetSchema");
			std::string schemaRef = targetSchema->getValue<std::string>("$ref");
			url = obj->getValue<std::string>("href");
			std::string method = obj->get("method");
			if (method.compare("get") != 0)
			{
				method = GET;
			}
			else
			{
				method = POST;
			}
			Poco::StringTokenizer str(schemaRef, "/", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			responseSchemaName = str[str.count()-1];
		}

		void writeCpp(FileOutputStream& cpp, const std::string& apiName)
		{
			cpp << "Poco::AutoPtr<" << responseSchemaName << "> " << apiName << "::" << name;
			if (method == GET)
			{
				cpp << "() ";
			}
			{
				scopedStream stream(cpp);
				cpp << "Poco::AutoPtr<" << responseSchemaName << "> retVal = new " << responseSchemaName << "()" << cendl;
				cpp << "Poco::JSON::Object::Ptr pResult = invoke(Poco::Net::HTTPRequest::";
				if (method == GET) cpp << "HTTP_GET"; else cpp << "HTTP_POST";
				cpp << ", \"" << url << "\")";
				cpp << cendl;
				cpp << "retVal->read(pResult)" << cendl;
				cpp << "return retVal" << cendl;
			}
			cpp << endl;
		}

		void writeHeader(FileOutputStream& header)
		{
			header << endl;
			header << "// " << description << endl;
			header << "Poco::AutoPtr<" << responseSchemaName << "\> " << name;
			if (method = GET)
			{
				header << "()";
			}
			header << cendl;
		}
	};

	void getAPIName(const std::string& apiFile, std::string& apiName)
	{
		Path p(apiFile);
		apiName = p.getBaseName();
	}

	void pushNameSpace(FileOutputStream& stream, std::string& namespacename)
	{
		if (!namespacename.empty())
		{
			stream << "namespace " << namespacename << " {" << endl;
			stream << endl;
			++stream;
		}
	}

	void popNameSpace(FileOutputStream& stream, std::string& namespacename)
	{
		if (!_namespace.empty())
		{
			--stream;
			stream << "} //" << namespacename << endl;
		 }
	}

	class scopedStream
	{
	public:
		enum IndentType
		{
			INC = 0,
			DEC
		};
		
		scopedStream(FileOutputStream& stream, bool brackets = true, IndentType indent = INC)
			: _stream(stream)
			, _indent(indent)
			, _brackets(brackets)
		{
			if (brackets) stream << "{" << endl;
			if (indent == INC) ++stream; else --stream;
		}

		~scopedStream()
		{
			if (_indent == INC) --_stream; else ++_stream;
			if (_brackets) _stream << "}" << endl;
		}

		IndentType _indent;
		FileOutputStream& _stream;
		bool _brackets;
	};

	void pushClass(FileOutputStream& stream, std::string& className, const char** parentClass , Poco::UInt32 length)
	{
		stream << "class " << className;
		Poco::UInt32 count = 0;
		for(Poco::UInt32 count = 0; count < length; count++)
		{
			if (count) stream << ", ";
			else stream << " : ";
			stream << " public " << parentClass[count];
			count++;
		}
		stream << " {";
		newLine(stream);
		++stream;

		//public section 
		{
			scopedStream scoped(stream, false, scopedStream::DEC);
			stream << "public:" << endl;
		}
		//declare constructor
		newLine(stream);
		stream << "// Constructor" << endl;
		stream << className << "()" << cendl;

		//declare destructor
		newLine(stream);
		stream << "// Destructor" << endl;
		stream << "~" << className << "()" << cendl;
		stream << endl;
	}

	void popClass(FileOutputStream& stream, std::string& className)
	{
		if (!className.empty())
		{
			--stream;
			stream << "}; //" << className << endl;
			newLine(stream);
		}
	}

	void startHeader(FileOutputStream& stream, const char** headerFile, Poco::UInt32 length)
	{
		stream << "#pragma once " << endl;
		Poco::UInt32 count = 0;
		for (Poco::UInt32 count = 0; count < length; count++)
		{
			stream << "#include \"" << headerFile[count] << "\"" << endl;
		}
		newLine(stream);
	}

	void startCpp(FileOutputStream& stream, const char** headerFile, Poco::UInt32 length)
	{
		stream << "#include \"stdafx.h\" " << endl;
		Poco::UInt32 count = 0;
		for (Poco::UInt32 count = 0; count < length; count++)
		{
			stream << "#include \"" << headerFile[count] << "\"" << endl;
		}
		newLine(stream);
	}

	void doAPIConstructor(FileOutputStream& cpp, const std::string& apiName, const Config& config)
	{
		cpp << apiName << "::" << apiName << "() ";
		{
			scopedStream scope(cpp);
			cpp << "_uri = \"" << config.baseUrl << "\"" << cendl;
		}
		cpp << endl;
	}

	void doConstructor(FileOutputStream& cpp, const std::string& className)
	{
		cpp << className << "::" << className << "() ";
		{
			scopedStream scope(cpp);
		}
		cpp << endl;

	}

	void doDestructor(FileOutputStream& cpp, const std::string& className)
	{
		cpp << className << "::~" << className << "() ";
		{
			scopedStream scope(cpp);
		}
		cpp << endl;
	}


    void processTemplate(const std::string& apiFile)
    {
        std::ostringstream ostr;
        Poco::FileInputStream fis(apiFile);
        Poco::StreamCopier::copyStream(fis, ostr);

        Poco::UInt32 headerIdent = 0;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(ostr.str());
        Poco::JSON::Object::Ptr api = result.extract<Poco::JSON::Object::Ptr>();

		std::string apiName;
		getAPIName(apiFile, apiName);

		Poco::JSON::Object::Ptr definitions = api->getObject("definitions");
		std::map<std::string, ObjectSchemaDefinition> schemaDefinitions;
		std::vector<std::string> definitionNames;
		definitions->getNames(definitionNames);
		for (auto& it : definitionNames)
		{
			Poco::JSON::Object::Ptr definition = definitions->getObject(it);
			Poco::JSON::Object::Ptr properties = definition->getObject("properties");
			ObjectSchemaDefinition def;
			def.read(properties);
			def.name = it;
			std::string key = "#/definitions/" + it;
			schemaDefinitions.insert(std::pair<std::string,ObjectSchemaDefinition>(key, def));
		}

		Poco::JSON::Array::Ptr methods = api->getArray("links");
		std::vector<EndPoint> endPoints;
		for (auto& it : *methods)
		{
			endPoints.emplace_back();
			EndPoint& endPoint = endPoints.back();
			endPoint.read(it.extract<Poco::JSON::Object::Ptr>());
		}

		Poco::JSON::Object::Ptr configObj = api->getObject("config");
		Config config;
		config.read(configObj);

		//Write
        std::string headerFileName = _outputDir + Path::separator() + apiName + ".h";
		File headerFile(headerFileName);
		FileOutputStream header(headerFileName, std::ios::out);

        std::string cppFileName = _outputDir + Path::separator() + apiName + ".cpp";
        FileOutputStream cpp(cppFileName, std::ios::out);

		const char* headerFiles[4] = {
			"Poco/Net/HTMLForm.h",
			"Poco/Util/AbstractConfiguration.h",
			"Poco/AutoPtr.h",
			"trader/Api.h"
		};

		startHeader(header, headerFiles, 4);
		newLine(header);
		pushNameSpace(header, _namespace);
			for (auto& schemaDefinition : schemaDefinitions)
			{
				ObjectSchemaDefinition& def = schemaDefinition.second;
				const char* baseClass[1] = { "Poco::RefCountedObject" };
				pushClass(header, def.name, baseClass, 1);
				def.writeHeader(header);
				popClass(header, def.name);
			}
			const char* baseClassNames[1] = { "Api" };
			pushClass(header, apiName, baseClassNames, 1);
			for (auto& endPoint : endPoints)
			{
				endPoint.writeHeader(header);
			}
			popClass(header, apiName);
		popNameSpace(header, _namespace);

		const char* cppHeaders[9];
		cppHeaders[0] = headerFileName.c_str();
		cppHeaders[1] = "Poco/Net/HTTPSClientSession.h";
		cppHeaders[2] = "Poco/Net/HTTPRequest.h";
		cppHeaders[3] = "Poco/Net/HTTPResponse.h";
		cppHeaders[4] = "Poco/Net/OAuth10Credentials.h";
		cppHeaders[5] = "Poco/Util/JSONConfiguration.h";
		cppHeaders[6] = "Poco/URI.h";
		cppHeaders[7] = "Poco/Format.h";
		cppHeaders[8] = "Poco/StreamCopier.h";
		startCpp(cpp, cppHeaders, 9);
		pushNameSpace(cpp, _namespace);
			for (auto& schemaDefinition : schemaDefinitions)
			{
				ObjectSchemaDefinition& def = schemaDefinition.second;
				doConstructor(cpp, def.name);
				doDestructor(cpp, def.name);
				def.writeCpp(cpp);
			}
			doAPIConstructor(cpp, apiName, config);
			doDestructor(cpp, apiName);
			for (auto& endPoint : endPoints)
			{
				endPoint.writeCpp(cpp, apiName);
			}
		popNameSpace(cpp, _namespace);
    }

    void processTemplates(const std::string& root)
    {
        DirectoryIterator it(root);
        DirectoryIterator end;
        while (it != end)
        {
            if (it->isDirectory())
            {
                processTemplates(it->path());
            }
            else
            {
                Path p(it->path());
                if (p.getExtension().compare("json") == 0)
                {
                    processTemplate(it->path());
                }
            }
            ++it;
        }
    }

    int main(const std::vector<std::string>& args)
    {
        try
        {
            if (_inputDir.empty())
            {
                _inputDir = Path::current() + "apis" + Path::separator();
            }

            if (_outputDir.empty())
            {
                _outputDir = Path::current() + "codegen" + Path::separator();
            }

			File outputDir(_outputDir);
			outputDir.createDirectories();

            processTemplates(_inputDir);
        }
        catch (Poco::Exception& exc)
        {
            std::cerr << exc.displayText() << std::endl;
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

private:
    std::string _inputDir;
    std::string _outputDir;
    std::string _namespace;
};

POCO_APP_MAIN(CodeGenApp)

