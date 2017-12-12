#pragma once

namespace trader {

    class Db : public Poco::RefCountedObject
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

        Poco::Data::Session* getDbSession()
        {
            return dbSession;
        }

    private:
        Poco::Data::Session* dbSession;
    };

    class DbManager : public SingletonHolder<DbManager>
    {
    public:
        DbManager()
        {}

        ~DbManager()
        {}

        void setDb(Poco::AutoPtr<Db> _db)
        {
            database = _db;
        }

        Poco::AutoPtr<Db> getDb()
        {
            return database;
        }

        static DbManager instance;

    private:
        Poco::AutoPtr<Db> database;
    };

}
