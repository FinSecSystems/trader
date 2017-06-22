#pragma once

#include "fileoutputstream.h"

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
	using namespace Poco::JSON;
	using namespace Poco;
	using namespace std;

	struct Config;

	struct EndPoint
	{
		enum Method {
			POST,
			GET
		};

		EndPoint(const Config& config)
			:_config(config)
		{}

		void read(JSON::Object::Ptr obj);
		void writeHeader(ApiFileOutputStream& header);
		void writeCpp(ApiFileOutputStream& cpp);

		string url;
		Method method;
		string description;
		string name;
		string responseSchemaName;
		const Config& _config;
	};
}


