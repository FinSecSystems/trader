#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"
#include "jsonschema.h"

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
	JsonSchema JsonSchema::instance;

	void JsonSchema::process(const string& namespacename, const string& filename, const string& outputdirectory)
	{
		ostringstream ostr;
		FileInputStream fis(filename);
		StreamCopier::copyStream(fis, ostr);

		JSON::Parser parser;
		Dynamic::Var result = parser.parse(ostr.str());
		JSON::Object::Ptr api = result.extract<JSON::Object::Ptr>();

		Config config;
		config.outputDir = outputdirectory;
		config.nameSpace = namespacename;
		getAPIName("config", filename, config.apiName);
		string apiName = config.apiName;
		std::transform(apiName.begin(), apiName.end(), apiName.begin(), ::tolower);
		config.headerFileName = outputdirectory + Path::separator() + apiName + ".h";
		config.cppFileName = outputdirectory + Path::separator() + apiName + ".cpp";

		ObjectSchemaDefinition def(config.apiName);
		def.read(api);

		//Write

		ApiFileOutputStream header(config.headerFileName);
		ApiFileOutputStream cpp(config.cppFileName);

		startHeader(header, 0);
		{
			ScopedNamespace scopedNamesapce(header, config.nameSpace);
			{
				ScopedClass<1> scopedClass(header, def.getName(), "Poco::RefCountedObject");
				construct_header(header, def.getName(), 0);
				def.writeHeader(header);
			}
		}

		startCpp(cpp, 1,
			config.headerFileName.c_str()
		);
		{
			ScopedNamespace scopedNamesapce(cpp, config.nameSpace);
			construct(cpp, def.getName(), 0);
			def.writeCpp(cpp);
		}
	}

}