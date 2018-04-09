#pragma once

#include "stdafx.h"
#include "endpoint.h"
#include "fileoutputstream.h"

namespace trader
{

    class CodeGenApp : public Application
    {
      public:
        CodeGenApp();

      protected:
        void defineOptions(OptionSet &options);
        void handleHelp(const string &name, const string &value);
        void handleInputDir(const string &name, const string &value);
        void handleInputFile(const string &name, const string &value);
        void handleOutputDir(const string &name, const string &value);
        void handleNamespace(const string &name, const string &value);
        void handleType(const string &name, const string &value);
        void displayHelp();
        void processDirectory(const string &root, std::function< void(const string &) > func);
        int main(const std::vector< string > &args);

      private:
        string _inputDir;
        string _inputFile;
        string _outputDir;
        string _namespace;
        string _type;
    };

} // namespace trader
