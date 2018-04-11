#pragma once

#include "app.h"

namespace trader
{

    class ApplicationHelper : public App
    {
      public:
        bool findFile(Poco::Path &path) const override;
        Poco::Util::AbstractConfiguration &appConfig();
        ThreadPool pool;

		friend class SampleAppTests_SetupApp_Test;
		friend class SampleAppTests_StartApp_Test;
		friend void setup(Poco::AutoPtr<trader::ApplicationHelper> pApp);

      protected:
        void defineOptions(Poco::Util::OptionSet &options);
        void handleHelp(const std::string &name, const std::string &value);
        void displayHelp();
        void setup();
        void start();
		void destroy();


	};

} // namespace trader
