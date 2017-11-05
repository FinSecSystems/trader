#include "stdafx.h"
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
#include "endpoint.h"
#include "fileoutputstream.h"
#pragma once


namespace trader {

	using namespace Poco;
	using namespace std;

	class CodeGenApp : public Application
	{
	public:
		CodeGenApp();

	protected:
		void defineOptions(OptionSet& options);
		void handleHelp(const string& name, const string& value);
		void handleInputDir(const string& name, const string& value);
		void handleInputFile(const string& name, const string& value);
		void handleOutputDir(const string& name, const string& value);
		void handleNamespace(const string& name, const string& value);
		void handleType(const string& name, const string& value);
		void displayHelp();
		void processDirectory(const string& root, std::function<void(const string&)> func);
		int main(const std::vector<string>& args);

	private:
		string _inputDir;
		string _inputFile;
		string _outputDir;
		string _namespace;
		string _type;
	};

}