#pragma once

namespace trader {

	class Db : public Poco::Util::Application
	{
	public:
        Db()
		{
		}

		virtual ~Db()
		{
			if (dbSession)
			{
				delete dbSession;
				dbSession = nullptr;
			}
		}

		virtual bool findFile(Poco::Path& path) const = 0;

		Poco::Data::Session* dbSession;
	};
}
