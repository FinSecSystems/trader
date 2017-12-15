#pragma once

namespace trader {

	class AppConnection : public Interface::Connection
	{
	public:
        AppConnection();

        ~AppConnection();

       // Poco::FIFOEvent<const KeyValueArgs< Poco::UInt64, Poco::AutoPtr< IMessageData > >, Poco::FastMutex > evt;

	};
}
