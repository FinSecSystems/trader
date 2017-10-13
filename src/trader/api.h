#pragma once

namespace trader {

	class Api
	{
	public:
        virtual ~Api() = 0;
		virtual Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri) = 0;
	};
}