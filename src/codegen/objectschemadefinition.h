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
#include "endpoint.h"
#include "fileoutputstream.h"
#pragma once

#include "utils.h"

namespace trader {

	using namespace Poco;
	using namespace std;

	struct ObjectSchemaDefinition
	{

		void read(JSON::Object::Ptr obj);
		void writeCpp(ApiFileOutputStream& cpp);
		void writeHeader(ApiFileOutputStream& cpp);
		void header_construct(JSON::Object::Ptr obj, ApiFileOutputStream& stream, string expandedName, string keyName, bool previousArray);
		void cpp_construct(JSON::Object::Ptr obj, ApiFileOutputStream& stream, expansionstringstream expandedName, string keyName, UInt32 objIndex, bool previousArray);
		void writeRestEncodedParams(ApiFileOutputStream& cpp);

		string name;
		JSON::Object::Ptr rootObj;
	};

}


