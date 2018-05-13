#pragma once

namespace trader
{

    class DATACONNECTOR_DLL App : public Poco::Util::Application
    {
      public:
        virtual bool findFile(Poco::Path &path) const = 0;
    };

    class DATACONNECTOR_DLL AppManager {
      public:
        AppManager() {}

        ~AppManager() {}

		void setApp(Poco::AutoPtr< App > _app) { application = _app; }

		Poco::AutoPtr< App > getApp() { return application; }

        static AppManager instance;

      private:
        Poco::AutoPtr< App > application;
    };
} // namespace trader
