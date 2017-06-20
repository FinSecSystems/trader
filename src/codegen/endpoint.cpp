#include "stdafx.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "utils.h"

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

	void EndPoint::read(JSON::Object::Ptr obj)
	{
		name = obj->getValue<string>("title");
		description = obj->getValue<string>("description");
		JSON::Object::Ptr targetSchema = obj->getObject("targetSchema");
		string schemaRef = targetSchema->getValue<string>("$ref");
		url = obj->getValue<string>("href");
		string methodString = obj->get("method");
		if (methodString.compare("get") != 0)
		{
			method = GET;
		}
		else
		{
			method = POST;
		}
		StringTokenizer str(schemaRef, "/", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
		responseSchemaName = str[str.count() - 1];
	}

	void EndPoint::writeCpp(ApiFileOutputStream& cpp)
	{
		cpp << "Poco::AutoPtr<" << responseSchemaName << "> " << _config.apiName << "::" << name;
		if (method == GET)
		{
			cpp << "() ";
		}
		{
			ScopedStream stream(cpp);
			cpp << "Poco::AutoPtr<" << responseSchemaName << "> retVal = new " << responseSchemaName << "()" << cendl;
			cpp << "Poco::JSON::Object::Ptr pResult = invoke(Poco::Net::HTTPRequest::";
			if (method == GET) cpp << "HTTP_GET"; else cpp << "HTTP_POST";
			cpp << ", \"" << url << "\")";
			cpp << cendl;
			cpp << "retVal->read(pResult)" << cendl;
			cpp << "return retVal" << cendl;
		}
		cpp << endl;
	}

	void EndPoint::writeHeader(ApiFileOutputStream& header)
	{
		header << endl;
		header << "// " << description << endl;
		header << "Poco::AutoPtr<" << responseSchemaName << "> " << name;
		if (method == GET)
		{
			header << "()";
		}
		header << cendl;
	}
}


