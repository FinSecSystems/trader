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


namespace trader {

	using namespace Poco;
	using namespace std;

	class FixSpec : public SingletonHolder<FixSpec>
	{
	public:
		void process(const string& _namespace, const string& _inputDir, const string& outputdirectory);
		const char* getCppType(const string& dbType);
		static FixSpec instance;
	};

}