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
#pragma warning( pop ) 


#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <algorithm>
#include <functional>
#include <stdarg.h>