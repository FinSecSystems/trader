#pragma once

namespace trader {

    class DATACONNECTOR_DLL Db : public Poco::RefCountedObject
    {
    public:
        Db(Poco::Data::Session* _dbSession)
            : dbSession(_dbSession)
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

    protected:
        Poco::Data::Session* dbSession;
    };

    class DATACONNECTOR_DLL DbManager : public SingletonHolder<DbManager>
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
