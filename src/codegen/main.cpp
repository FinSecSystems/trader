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
#include <iostream>
#include <iomanip>
#include <sstream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Path;

class CodeGenApp : public Application
{
public:
    CodeGenApp()
    {
    }

protected:
    void defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h", "Display help information on command line arguments.")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleHelp)));

        options.addOption(
            Option("outputdir", "o", "Location to write cpp and header files")
            .required(false)
            .repeatable(false)
            .argument("output directory")
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleOutputDir)));

        options.addOption(
            Option("inputdir", "i", "Location of the API JSON files")
            .required(false)
            .repeatable(false)
            .argument("input directory")
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleInputDir)));

        options.addOption(
            Option("namespace", "n", "Namespace")
            .required(false)
            .repeatable(false)
            .argument("input directory")
            .callback(OptionCallback<CodeGenApp>(this, &CodeGenApp::handleNamespace)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        displayHelp();
        stopOptionsProcessing();
    }

    void handleInputDir(const std::string& name, const std::string& value)
    {
        _inputDir = value;
    }

    void handleOutputDir(const std::string& name, const std::string& value)
    {
        _outputDir = value;
    }

    void handleNamespace(const std::string& name, const std::string& value)
    {
        _namespace = value;
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A simple command line client for posting status updates.");
        helpFormatter.format(std::cout);
    }

    class FileOutputStream
    {
    public:

        FileOutputStream& operator++()
        {
            // actual increment takes place here
            indentation++;
            return *this;
        }

        FileOutputStream& operator--()
        {
            // actual increment takes place here
            indentation--;
            return *this;
        }

        FileOutputStream(const std::string& path, std::ios::openmode mode = std::ios::out | std::ios::trunc)
            : stream(path, mode)
            ,indentation(0)
        {}

        class tabs // injects some `X`s into the stream
        {
            std::size_t _n;
        public:
            explicit tabs(std::size_t n) : _n(n) {}
            std::size_t getn() const { return _n; }
            friend std::ostream& operator<<(std::ostream& os, const tabs& obj)
            {
                std::size_t n = obj.getn();
                for (std::size_t i = 0; i < n; ++i)
                    os << "    ";
                return os;
            }
        };

        friend FileOutputStream& operator<<(FileOutputStream& os, const char* text)
        {
            os.tempStream << text;
            return os;
        }

        friend FileOutputStream& operator<<(FileOutputStream& os, std::string& str)
        {
            os.tempStream << str;
            return os;
        }

        friend FileOutputStream& operator<<(FileOutputStream& os, FileOutputStream& (*_Pfn)(FileOutputStream&))
        {	// call basic_ostream manipulator
            return ((*_Pfn)(os));
        }

        friend FileOutputStream & endl(FileOutputStream & os)
        {
            os.stream << std::endl;
            os.stream << tabs(os.indentation);
            os.stream << os.tempStream.str();
            os.tempStream.str("");
            os.tempStream.clear();
            return os;
        }

        Poco::UInt32 indentation;
        Poco::FileOutputStream stream;
        std::ostringstream tempStream;
    };




    void processTemplate(const std::string& apiFile)
    {
        std::ostringstream ostr;
        Poco::FileInputStream fis(apiFile);
        Poco::StreamCopier::copyStream(fis, ostr);

        Poco::UInt32 headerIdent = 0;

        std::string jsonStr = ostr.str();
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonStr);
        Poco::JSON::Object::Ptr api = result.extract<Poco::JSON::Object::Ptr>();

        std::string name = api->get("name");

        std::string headerFileName = _outputDir + Path::separator() + name + ".h";
        FileOutputStream header(headerFileName, std::ios::out);

        std::string cppFileName = _outputDir + Path::separator() + name + ".cpp";
        FileOutputStream cpp(cppFileName, std::ios::out);
        cpp << "#include \"stdafx.h\"" << endl;

        header << "#pragma once" << endl;
        header << endl;
        if (!_namespace.empty())
        {
            header << "namespace " << _namespace << " {" << endl;
            header << endl;
            ++header;
        }
        header << "class " << name << "{" << endl;
        header << endl;
        ++header;

        std::string uri = api->get("uri");
        Poco::JSON::Array::Ptr methods = api->getArray("methods");

        if (!_namespace.empty())
        {
            cpp << "namespace " << _namespace << " {" << endl;
        }

        for (auto& it : *methods)
        {
            Poco::JSON::Object::Ptr method = it.extract<Poco::JSON::Object::Ptr>();
            std::string name = method->get("name");
            std::string extension = method->get("extension");
            std::string description = method->get("description");
            std::string type = method->get("type");
            header << "// " << description endl;
            header << "void " << name << "();" << endl;
            header << endl;

        }

        //CPP Close Namespace
        if (!_namespace.empty())
        {
            cpp << "}" << endl;
        }
    
        //Header Close Class
        --header;
        header << "};" << endl;
        header << endl;

        //Header Close Namespace
        if (!_namespace.empty())
        {
            --header;
            header << "}" << endl;
        }
    }

    void processTemplates(const std::string& root)
    {
        DirectoryIterator it(root);
        DirectoryIterator end;
        while (it != end)
        {
            if (it->isDirectory())
            {
                processTemplates(it->path());
            }
            else
            {
                Path p(it->path());
                if (p.getExtension().compare("json") == 0)
                {
                    processTemplate(it->path());
                }
            }
            ++it;
        }
    }

    int main(const std::vector<std::string>& args)
    {
        try
        {
            if (_inputDir.empty())
            {
                _inputDir = Path::current() + "apis" + Path::separator();
            }

            if (_outputDir.empty())
            {
                _outputDir = Path::current() + "codegen" + Path::separator();
            }

           
            processTemplates(_inputDir);
        }
        catch (Poco::Exception& exc)
        {
            std::cerr << exc.displayText() << std::endl;
            return Application::EXIT_SOFTWARE;
        }
        return Application::EXIT_OK;
    }

private:
    std::string _inputDir;
    std::string _outputDir;
    std::string _namespace;
};

POCO_APP_MAIN(CodeGenApp)

