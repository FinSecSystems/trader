
#include "targetver.h"
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#include "Poco/Poco.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/OAuth10Credentials.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/URI.h"
#include "Poco/Format.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/SHA1Engine.h"
#include "Poco/HMACEngine.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base32Encoder.h"
#include "Poco/HexBinaryEncoder.h"
#include "Poco/Exception.h"
#include "Poco/InflatingStream.h"
#pragma warning(pop)
#include <ctime>
#include <regex>
#include <limits>
