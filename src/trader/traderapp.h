#pragma once

namespace trader {

	class TraderApp : public App
	{
	public:
        TraderApp()
		{
		}

		~TraderApp()
		{
		}

		bool findFile(Poco::Path& path) const override;

        Poco::AutoPtr<Db> dB;

	protected:
		void defineOptions(Poco::Util::OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void displayHelp();
        Poco::Util::AbstractConfiguration& appConfig();
		int main(const std::vector<std::string>& args);

	};
}
