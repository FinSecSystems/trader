#pragma once

namespace trader {

	class MarketDataSubSystem : public Poco::Util::Subsystem, public Poco::Runnable
	{
	public:
        MarketDataSubSystem() :
            app(nullptr)
		{
		}

		~MarketDataSubSystem()
		{
		}

        const char* name() const override
        {
            return "MarketData";
        }

    protected:
        void initialize(Application& application) override;

        void uninitialize() override;

        void run() override;

        TraderApp* app;
	};
}
