#pragma once

#include "endpoint.h"
#include "fileoutputstream.h"
#include <unordered_map>


namespace trader {

	using namespace Poco;
	using namespace std;

	class FixSpec : public SingletonHolder<FixSpec>
	{
	public:
		void process(const string& _namespace, const string& _inputDir, const string& outputdirectory);
		const char* getCppType(const string& dbName, const string& dbType);
        enum InterfaceType
        {
            InterfaceType_STRING,
            InterfaceType_DOUBLE,
            InterfaceType_FLOAT,
            InterfaceType_INTEGER,
            InterfaceType_BOOL,
            InterfaceType_ENUM,
            NUM_InterfaceType
        };
        string getDefaultType(const string &dbName, InterfaceType interfaceType);
        typedef std::unordered_map<std::string, InterfaceType> TypenameToTypeMap;
        TypenameToTypeMap typenameToTypeMap;
		static FixSpec instance;
	};

}