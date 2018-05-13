#include "Poco/Platform.h"
#if defined(POCO_OS_FAMILY_WINDOWS) 
#include "targetver.h"
#endif
#pragma warning( push )  
#pragma warning( disable : 4244 )  
#pragma warning( disable : 4127 )  
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
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/Exception.h"
#include "Poco/Debugger.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"

#pragma warning( pop ) 

#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <algorithm>
#include <functional>
#include <stdarg.h>

using Poco::DirectoryIterator;
using Poco::Exception;
using Poco::File;
using Poco::Path;
using Poco::Util::AbstractConfiguration;
using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;
using Poco::XML::AutoPtr;
using Poco::XML::Document;
using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Node;
using Poco::XML::NodeFilter;
using Poco::XML::NodeIterator;
using Poco::XML::NodeList;
using namespace Poco;
using namespace std;
using namespace Poco::XML;
