#pragma once

#include "endpoint.h"
#include "fileoutputstream.h"
#include "utils.h"
#include "objectschemadefinition.h"

namespace trader {
	using namespace Poco;
	using namespace std;

	struct Config
	{
		void read(JSON::Object::Ptr obj)
		{
			baseUrl = obj->getValue<string>("baseurl");
		}

		string baseUrl;
		string inputDir;
		string outputDir;
		string nameSpace;
		string apiName;
		string headerFileName;
		string cppFileName;
	};
}


