#include "stdafx.h"

#include "endpoint.h"
#include "fileoutputstream.h"
#include "helpers.h"
#include "objectschemadefinition.h"
#include "config.h"
#include "hyperschema.h"
#include "app.h"
#include "jsonschema.h"
#include "databaseschema.h"

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

	CodeGenApp::CodeGenApp() {}

	void CodeGenApp::defineOptions(OptionSet& options)
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
			.argument("namespace")
			.callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleNamespace)));

		options.addOption(
			Option("type", "t", "Json file Type. hyperschema, jsonschema")
			.required(true)
			.repeatable(false)
			.argument("type")
			.callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleType)));
	}

	void CodeGenApp::handleHelp(const string& name, const string& value)
	{
		(void)value; (void)name;
		displayHelp();
		stopOptionsProcessing();
	}

	void CodeGenApp::handleInputDir(const string& name, const string& value)
	{
		(void)name;
		_inputDir = value;
	}

	void CodeGenApp::handleOutputDir(const string& name, const string& value)
	{
		(void)name;
		_outputDir = value;
	}

	void CodeGenApp::handleNamespace(const string& name, const string& value)
	{
		(void)name;
		_namespace = value;
	}

	void CodeGenApp::handleType(const string& name, const string& value)
	{
		(void)name;
		_type = value;
	}

	void CodeGenApp::displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A simple command line client for posting status updates.");
		helpFormatter.format(std::cout);
	}

	void CodeGenApp::processDirectory(const string& root, std::function<void(const string&)> func)
	{
		DirectoryIterator it(root);
		DirectoryIterator end;
		while (it != end)
		{
			if (it->isDirectory())
			{
				func(it->path());
			}
			else
			{
				Path p(it->path());
				if (p.getExtension().compare("json") == 0)
				{
					func(it->path());
				}
			}
			++it;
		}
	}

	int CodeGenApp::main(const std::vector<string>& args)
	{
		(void)args;
		try
		{
			using namespace std::placeholders;

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

			if (_type.compare("hyperschema") == 0)
			{
				processDirectory(_inputDir, std::bind(&HyperSchema::process, HyperSchema::instance.get(), _namespace, _1, _outputDir));
			}
			else if (_type.compare("jsonschema") == 0)
			{
				processDirectory(_inputDir, std::bind(&JsonSchema::process, JsonSchema::instance.get(), _namespace, _1, _outputDir));
			}
			else if (_type.compare("databaseschema") == 0)
			{
				processDirectory(_inputDir, std::bind(&DatabaseSchema::process, DatabaseSchema::instance.get(), _namespace, _1, _outputDir));
			}

			ostringstream message;
			message << _type << " generation complete..." << std::endl;
			std::cout << message.str();
#if defined(POCO_OS_FAMILY_WINDOWS) 
			OutputDebugStringA(message.str().c_str());
#endif
		}
		catch (Exception& exc)
		{
			std::cerr << exc.displayText() << std::endl;
			return Application::EXIT_SOFTWARE;
		}
		return Application::EXIT_OK;
	}

}

POCO_APP_MAIN(trader::CodeGenApp)

