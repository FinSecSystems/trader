#pragma once

namespace trader {

	class App : public Poco::Util::Application
	{
	public:
		App()
		{
		}

		~App()
		{
			if (dbSession)
			{
				delete dbSession;
				dbSession = nullptr;
			}
		}

		bool findFile(Poco::Path& path) const;

		friend class Fyb;
		friend class Exchangeratelab;
	protected:
		void defineOptions(Poco::Util::OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void displayHelp();
        Poco::Util::AbstractConfiguration& appConfig();
		int main(const std::vector<std::string>& args);

	private:
		Poco::Data::Session* dbSession;
	};
}
