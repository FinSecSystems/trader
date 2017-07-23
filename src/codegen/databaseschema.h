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

	class DatabaseSchema : public SingletonHolder<DatabaseSchema>
	{
	public:
		void process(const string& _namespace, const string& _inputDir, const string& outputdirectory);
		void generateInsertAndDeleteUnchanged(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
		void generateInsert(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
		void generateClear(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string& name);
		void generateInit(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string& name);
		void generateInsertOnce(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
		void generateInsertUnique(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
		void generateInsertMultiple(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
		void generateInsertUniqueMultiple(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
		void generateGetLatest(ApiFileOutputStream& cpp, ostringstream& nameStream, string& apiName, ostringstream& keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);

		static DatabaseSchema instance;
	};

}