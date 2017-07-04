#include "stdafx.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"

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
		JSON::Object::Ptr targetSchema = obj->getObject("targetSchema");
		string targetSchemaRef = targetSchema->getValue<string>("$ref");
		StringTokenizer str(targetSchemaRef, "/", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
		responseSchemaName = str[str.count() - 1];
		JSON::Object::Ptr schema = obj->getObject("schema");
		if (schema)
		{
			string schemaRef = schema->getValue<string>("$ref");
			StringTokenizer str2(schemaRef, "/", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
			inputSchemaName = str2[str2.count() - 1];
		}
	}

	void EndPoint::writeCpp(ApiFileOutputStream& cpp)
	{
		cpp << "Poco::AutoPtr<" << responseSchemaName << "> " << _config.apiName << "::" << name;
		if (method == GET)
		{
			cpp << "(";
			if (!inputSchemaName.empty())
			{
				cpp << "Poco::AutoPtr<" << inputSchemaName << "> " << var_name(inputSchemaName);
			}
			cpp << ")";
		}
		{
			ScopedStream<ApiFileOutputStream> stream(cpp);
			cpp << "std::ostringstream uri" << cendl;
			cpp << "uri << \"" << url << "\"" << cendl;
			if (!inputSchemaName.empty())
			{
				string inputSchemaRefStr = "#/definitions/" + inputSchemaName;
				auto found = _config.schemaDefinitions.find(inputSchemaRefStr);
				if (found != _config.schemaDefinitions.end())
				{
					ObjectSchemaDefinition& obj = found->second;
					obj.writeRestEncodedParams(cpp);
				}
			}
			cpp << "Poco::AutoPtr<" << responseSchemaName << "> retVal = new " << responseSchemaName << "()" << cendl;
			cpp << "Poco::Dynamic::Var pResult = invoke(Poco::Net::HTTPRequest::";
			if (method == GET) cpp << "HTTP_GET"; else cpp << "HTTP_POST";
			cpp << ", uri.str())" << cendl;
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
			header << "(";
			if (!inputSchemaName.empty())
			{
				header << "Poco::AutoPtr<" << inputSchemaName << "> " << var_name(inputSchemaName);
			}
			header << ")";
		}
		header << cendl;
	}
}


