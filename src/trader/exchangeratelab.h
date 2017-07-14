#pragma once


namespace trader {

	class Exchangeratelab
	{
	public:
		Exchangeratelab();

		~Exchangeratelab();

		virtual Poco::Dynamic::Var invoke(const std::string& httpMethod, Poco::URI& uri);

	protected:
		Exchangeratelab(const Exchangeratelab&);
		Exchangeratelab& operator = (const Exchangeratelab&);

		std::string _uri;
	};

}