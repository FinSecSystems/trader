#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"
#include "hyperschema.h"

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
	HyperSchema HyperSchema::instance;

	void HyperSchema::process(const string& namespacename, const string& filename, const string& outputdirectory)
	{
		ostringstream ostr;
		FileInputStream fis(filename);
		StreamCopier::copyStream(fis, ostr);

		JSON::Parser parser;
		Dynamic::Var result = parser.parse(ostr.str());
		JSON::Object::Ptr api = result.extract<JSON::Object::Ptr>();

		JSON::Object::Ptr configObj = api->getObject("config");
		Config config;
		config.read(configObj);
		config.outputDir = outputdirectory;
		config.nameSpace = namespacename;
		getAPIName("api", filename, config.apiName);
		string apiName = config.apiName;
		std::transform(apiName.begin(), apiName.end(), apiName.begin(), ::tolower);
		config.headerFileName = outputdirectory + Path::separator() + apiName + ".h";
		config.cppFileName = outputdirectory + Path::separator() + apiName + ".cpp";
		string name;
		getAPIName("", filename, name);
		string configClassName;
		getAPIName("config", filename, configClassName);

		JSON::Object::Ptr definitions = api->getObject("definitions");

		vector<string> definitionNames;
		definitions->getNames(definitionNames);
		for (auto& it : definitionNames)
		{
			JSON::Object::Ptr definition = definitions->getObject(it);
			JSON::Object::Ptr properties = definition->getObject("properties");
			ObjectSchemaDefinition def(it);
			def.read(definition);
			string key = "#/definitions/" + it;
			config.schemaDefinitions.insert(std::pair<string, ObjectSchemaDefinition>(key, def));
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

		ostringstream baseHeaderName;
		string headerName = name;
		std::transform(headerName.begin(), headerName.end(), headerName.begin(), ::tolower);
		baseHeaderName << "trader/" << headerName << ".h";

		ostringstream configHeaderName;
		string configHeaderStr = configClassName;
		std::transform(configHeaderStr.begin(), configHeaderStr.end(), configHeaderStr.begin(), ::tolower);
		configHeaderName << configHeaderStr << ".h";

		ostringstream appPtrStream;
		appPtrStream << "Poco::AutoPtr<" << namespacename << "::App>";

		ostringstream baseUrlStream;
		baseUrlStream << "\"" << config.baseUrl << "\"";

		startHeader(header, 3,
			baseHeaderName.str().c_str(),
			configHeaderName.str().c_str(),
			"trader/app.h"
			);
		{
			ScopedNamespace scopedNamesapce(header, config.nameSpace);
			for (auto& schemaDefinition : config.schemaDefinitions)
			{
				ObjectSchemaDefinition& def = schemaDefinition.second;
				{
					ScopedClass<1> scopedClass(header, def.getName(), "Poco::RefCountedObject");
					construct_header(header, def.getName(), 0);
					def.writeHeader(header);
				}
			}
			{
				ScopedClass<1> scopedClass(header, config.apiName, name.c_str());
				construct_header(header, config.apiName, 2
					, appPtrStream.str().c_str(), "app"
				);
				for (auto& endPoint : endPoints)
				{
					endPoint.writeHeader(header);
				}
				if (config.useConfig)
				{
					header << endl;
					header << configClassName << tabs(1) << "config" << cendl;
				}
				header << endl;
				header << "Poco::AutoPtr<" << namespacename << "::App>" << tabs(1) << "_app" << cendl;
			}
		}

		startCpp(cpp, 2,
			config.headerFileName.c_str(),
			"trader/app.h"
		);
		{
			ScopedNamespace scopedNamesapce(cpp, config.nameSpace);
			for (auto& schemaDefinition : config.schemaDefinitions)
			{
				ObjectSchemaDefinition& def = schemaDefinition.second;
				construct(cpp, def.getName(), 0);
				def.writeCpp(cpp);
			}

			if (config.useConfig)
			{
				ostringstream pathStatement;
				string nameStr = name;
				std::transform(nameStr.begin(), nameStr.end(), nameStr.begin(), ::tolower);
				pathStatement << "Poco::Path filePath(\"" << nameStr << ".config.json\");";

				construct_ex(cpp, config.apiName, 2, 4, 4
					, appPtrStream.str().c_str(), "app"
					, "_uri", baseUrlStream.str().c_str()
					, "_app", "app"
					, pathStatement.str().c_str()
					, "if (app->findFile(filePath)) {"
					, "\tconfig.readFile(filePath.toString());"
					, "}"
				);
			}
			else
			{
				construct_ex(cpp, config.apiName, 2, 4, 0
					, appPtrStream.str().c_str(), "app"
					, "_uri", baseUrlStream.str().c_str()
					, "_app", "app"
				);
			}

			for (auto& endPoint : endPoints)
			{
				endPoint.writeCpp(cpp);
			}
		}
	}

}