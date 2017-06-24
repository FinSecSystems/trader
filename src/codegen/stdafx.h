
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

#include "defines.h"
#if defined(_DEBUG)
#define TASK_SCHEDULER_DEBUG TASK_SCHEDULER_ENABLED
#else
#define TASK_SCHEDULER_DEBUG TASK_SCHEDULER_DISABLED
#endif // defined(_DEBUG)
#define TASK_SCHEDULER_ASSERT TASK_SCHEDULER_ENABLED
#define TASK_SCHEDULER_PROFILER TASK_SCHEDULER_PROFILER_NONE
#include "platform.h"
#include "utils.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>

