#pragma once

#include "endpoint.h"
#include "fileoutputstream.h"

namespace trader
{

    class DatabaseSchema : public SingletonHolder< DatabaseSchema >
    {
      public:
        void process(const string &_namespace, const string &_inputDir, const string &outputdirectory);
        void generateInsertAndDeleteUnchanged(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                                              ostringstream &keyStream, JSON::Object::Ptr table,
                                              JSON::Array::Ptr fields);
        void generateInsert(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                            ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateClear(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                           ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string &name);
        void generateInit(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                          ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields, string &name);
        void generateInsertOnce(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                                ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateInsertUnique(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                                  ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateInsertMultiple(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                                    ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateDeleteMultiple(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                                    ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateInsertUniqueMultiple(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                                          ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateGetLatest(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                               ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);
        void generateGetAll(ApiFileOutputStream &cpp, ostringstream &nameStream, string &apiName,
                            ostringstream &keyStream, JSON::Object::Ptr table, JSON::Array::Ptr fields);

        static DatabaseSchema instance;
    };

} // namespace trader
