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
		getAPIName(filename, config.apiName);
		config.headerFileName = outputdirectory + Path::separator() + config.apiName + ".h";
		config.cppFileName = outputdirectory + Path::separator() + config.apiName + ".cpp";

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

		startHeader(header, 1,
			"trader/Api.h");
		{
			ScopedNamespace scopedNamesapce(header, config.nameSpace);
			for (auto& schemaDefinition : config.schemaDefinitions)
			{
				ObjectSchemaDefinition& def = schemaDefinition.second;
				{
					ScopedClass<1> scopedClass(header, def.getName(), "Poco::RefCountedObject");
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

		startCpp(cpp, 1,
			config.headerFileName.c_str()
		);
		{
			ScopedNamespace scopedNamesapce(cpp, config.nameSpace);
			for (auto& schemaDefinition : config.schemaDefinitions)
			{
				ObjectSchemaDefinition& def = schemaDefinition.second;
				construct(cpp, def.getName(), 0);
				def.writeCpp(cpp);
			}
			construct(cpp, config.apiName, 2, "_uri", config.baseUrl.c_str());
			for (auto& endPoint : endPoints)
			{
				endPoint.writeCpp(cpp);
			}
		}
	}

}