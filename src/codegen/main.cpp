#include "stdafx.h"

#include "endpoint.h"
#include "fileoutputstream.h"
#include "utils.h"
#include "objectschemadefinition.h"
#include "config.h"

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

namespace trader {

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

		void handleHelp(const string& name, const string& value)
		{
			displayHelp();
			stopOptionsProcessing();
		}

		void handleInputDir(const string& name, const string& value)
		{
			_inputDir = value;
		}

		void handleOutputDir(const string& name, const string& value)
		{
			_outputDir = value;
		}

		void handleNamespace(const string& name, const string& value)
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

		void processHyperSchema(const string& apiFile)
		{
			ostringstream ostr;
			FileInputStream fis(apiFile);
			StreamCopier::copyStream(fis, ostr);

			UInt32 headerIdent = 0;

			JSON::Parser parser;
			Dynamic::Var result = parser.parse(ostr.str());
			JSON::Object::Ptr api = result.extract<JSON::Object::Ptr>();

			JSON::Object::Ptr configObj = api->getObject("config");
			Config config;
			config.read(configObj);
			config.inputDir = _inputDir;
			config.outputDir = _outputDir;
			config.nameSpace = _namespace;
			getAPIName(apiFile, config.apiName);
			config.headerFileName = _outputDir + Path::separator() + config.apiName + ".h";
			config.cppFileName = _outputDir + Path::separator() + config.apiName + ".cpp";
		
			JSON::Object::Ptr definitions = api->getObject("definitions");
			map<string, ObjectSchemaDefinition> schemaDefinitions;
			vector<string> definitionNames;
			definitions->getNames(definitionNames);
			for (auto& it : definitionNames)
			{
				JSON::Object::Ptr definition = definitions->getObject(it);
				JSON::Object::Ptr properties = definition->getObject("properties");
				ObjectSchemaDefinition def;
				def.read(definition);
				def.name = it;
				string key = "#/definitions/" + it;
				schemaDefinitions.insert(std::pair<string, ObjectSchemaDefinition>(key, def));
			}

			JSON::Array::Ptr methods = api->getArray("links");
			std::vector<EndPoint> endPoints;
			for (auto& it : *methods)
			{
				endPoints.emplace_back(config);
				EndPoint& endPoint = endPoints.back();
				endPoint.read(it.extract<JSON::Object::Ptr>());
			}

			//Write

			ApiFileOutputStream header(config.headerFileName);
			ApiFileOutputStream cpp(config.cppFileName);

			startHeader(header, 4,
				"Poco/Net/HTMLForm.h",
				"Poco/Util/AbstractConfiguration.h",
				"Poco/AutoPtr.h",
				"trader/Api.h");
			{
				ScopedNamespace scopedNamesapce(header, config.nameSpace);
				for (auto& schemaDefinition : schemaDefinitions)
				{
					ObjectSchemaDefinition& def = schemaDefinition.second;
					{
						ScopedClass<1> scopedClass(header, def.name, "Poco::RefCountedObject");
						def.writeHeader(header);
					}
				}
				{
					ScopedClass<1> scopedClass(header, config.apiName, "Api");
					for (auto& endPoint : endPoints)
					{
							endPoint.writeHeader(header);
					}
				}
			}

			startCpp(cpp, 9,
				"Poco/Net/HTTPSClientSession.h",
				"Poco/Net/HTTPRequest.h",
				"Poco/Net/HTTPResponse.h",
				"Poco/Net/OAuth10Credentials.h",
				"Poco/Util/JSONConfiguration.h",
				"Poco/URI.h",
				"Poco/Format.h",
				"Poco/StreamCopier.h",
				config.headerFileName.c_str()
			);
			{
				ScopedNamespace scopedNamesapce(cpp, config.nameSpace);
				for (auto& schemaDefinition : schemaDefinitions)
				{
					ObjectSchemaDefinition& def = schemaDefinition.second;
					construct(cpp, def.name, 0);
					def.writeCpp(cpp);
				}
				construct(cpp, config.apiName, 2, "_uri", config.baseUrl.c_str());
				for (auto& endPoint : endPoints)
				{
					endPoint.writeCpp(cpp);
				}
			}

		}

		void processHyperSchemas(const string& root)
		{
			DirectoryIterator it(root);
			DirectoryIterator end;
			while (it != end)
			{
				if (it->isDirectory())
				{
					processHyperSchema(it->path());
				}
				else
				{
					Path p(it->path());
					if (p.getExtension().compare("json") == 0)
					{
						processHyperSchema(it->path());
					}
				}
				++it;
			}
		}

		int main(const std::vector<string>& args)
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

				processHyperSchemas(_inputDir);
			}
			catch (Exception& exc)
			{
				std::cerr << exc.displayText() << std::endl;
				return Application::EXIT_SOFTWARE;
			}
			return Application::EXIT_OK;
		}

	private:
		string _inputDir;
		string _outputDir;
		string _namespace;
	};

}

POCO_APP_MAIN(trader::CodeGenApp)

