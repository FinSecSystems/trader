#pragma once

#include "app.h"

namespace trader {

    class ApplicationHelper : public App
    {
    public:

        bool findFile(Poco::Path& path) const override;
        Poco::Util::AbstractConfiguration& appConfig();
        ThreadPool pool;

    protected:
        void defineOptions(Poco::Util::OptionSet& options);
        void handleHelp(const std::string& name, const std::string& value);
        void displayHelp();
        void setup();
        void start();
    };

 }
