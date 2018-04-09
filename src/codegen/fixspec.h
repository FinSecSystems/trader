#pragma once

#include "endpoint.h"
#include "fileoutputstream.h"


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