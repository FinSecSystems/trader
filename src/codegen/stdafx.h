
#include "targetver.h"
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
#pragma warning( pop )  
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>

