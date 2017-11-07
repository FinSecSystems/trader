#include "stdafx.h"

#include "config.h"
#include "fileoutputstream.h"
#include "endpoint.h"
#include "helpers.h"
#include "fixspec.h"

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Path;
using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Document;
using Poco::XML::NodeIterator;
using Poco::XML::NodeFilter;
using Poco::XML::Node;
using Poco::XML::NodeList;
using Poco::XML::AutoPtr;
using Poco::Exception;
using namespace Poco;
using namespace std;
using namespace Poco::XML;

namespace trader {
	FixSpec FixSpec::instance;

	const char* FixSpec::getCppType(const string& dbType)
	{
		if (dbType.compare("STRING") == 0
            || dbType.compare("CHAR") == 0
            || dbType.compare("CURRENCY") == 0)
		{
			return "std::string";
		}
		else if (dbType.compare("PRICE") == 0
            || dbType.compare("QTY") == 0
            || dbType.compare("AMT") == 0
            )
		{
			return "double";
		}
		else if (dbType.compare("SEQNUM") == 0
			|| dbType.compare("INT") == 0
			|| dbType.compare("UTCTIMESTAMP") == 0
			|| dbType.compare("LENGTH") == 0)
		{
			return "POCO::Int32";
		}
		else if (dbType.compare("BOOLEAN") == 0)
		{
			return "bool";
		}
		return dbType.c_str();
	}

	void FixSpec::process(const string& namespacename, const string& filename, const string& outputdirectory)
	{
		InputSource src(filename);
		DOMParser parser;
		AutoPtr<Document> pDoc = parser.parse(&src);

		Element* root = (Element*)pDoc->firstChild();
		Element* fieldsNode = root->getChildElement("fields");
        NodeList* fieldNodeList = fieldsNode->childNodes();

		Config config;
		config.outputDir = outputdirectory;
		config.nameSpace = namespacename;
		config.headerFileName = outputdirectory + Path::separator() + "interface.h";
		config.cppFileName = outputdirectory + Path::separator() + "interface.cpp";
	

		ApiFileOutputStream header(config.headerFileName);
		ApiFileOutputStream cpp(config.cppFileName);

        startHeader(header, 0);
        {
            ScopedNamespace scopedNamespaceTrader(header, config.nameSpace);
            {
                ScopedNamespace scopedNamespaceInterface(header, std::string("Interface"));

                for (UInt32 i = 0; i < fieldNodeList->length(); i++)
                {
                    Node* child = fieldNodeList->item(i);
                    if (child->nodeType() == Node::ELEMENT_NODE)
                    {
                        Element* fieldNode = (Element*)child;
                        string name = fieldNode->getAttribute("name");
                        string type = fieldNode->getAttribute("type");
                        string cppType = getCppType(type);
                        header << "typename " << cppType << " " << name << cendl;
                    }
                }
            }
        }


		//Write


		header << endl;

		cpp << endl;
	}

}