
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#include "Poco/AutoPtr.h"
#include "Poco/Base32Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/TypeHandler.h"
#include "Poco/Exception.h"
#include "Poco/FIFOEvent.h"
#include "Poco/File.h"
#include "Poco/FileChannel.h"
#include "Poco/FileStream.h"
#include "Poco/Format.h"
#include "Poco/FormattingChannel.h"
#include "Poco/HMACEngine.h"
#include "Poco/HexBinaryEncoder.h"
#include "Poco/InflatingStream.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Logger.h"
#include "Poco/Message.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPDigestCredentials.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/OAuth10Credentials.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Poco.h"
#include "Poco/SHA1Engine.h"
#include "Poco/SHA2Engine.h"
#include "Poco/SplitterChannel.h"
#include "Poco/Stopwatch.h"
#include "Poco/StreamCopier.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Timer.h"
#include "Poco/URI.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "targetver.h"
#pragma warning(pop)
#include <atomic>
#include <chrono>
#include <ctime>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <regex>
#include <sstream>
#include <unordered_map>

#include <dataconnector.h>
#include <interface.h>

using Poco::AutoPtr;
using Poco::Channel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Formatter;
using Poco::FormattingChannel;
using Poco::Logger;
using Poco::Message;
using Poco::PatternFormatter;
using Poco::SplitterChannel;
using Poco::Stopwatch;
using Poco::Thread;
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Data::AbstractBinder;
using Poco::Data::AbstractExtractor;
using Poco::Data::AbstractPreparator;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::TypeHandler;
using Poco::Util::AbstractConfiguration;
using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;
using namespace std;
using namespace std::chrono;
using namespace Poco;
using namespace Poco::Data::Keywords;
using namespace Poco::Net;
using namespace std::placeholders;

using namespace trader;
using namespace trader::Interface;
