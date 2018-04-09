#pragma once

#include "stdafx.h"
#include "endpoint.h"
#include "fileoutputstream.h"

namespace trader
{

    struct ObjectSchemaDefinition
    {
        ObjectSchemaDefinition(const string &_name);
        const string &getName();
        void read(JSON::Object::Ptr obj);
        void writeCpp(ApiFileOutputStream &cpp);
        void writeHeader(ApiFileOutputStream &cpp);
        void writeRestEncodedParams(ApiFileOutputStream &cpp);

      private:
        void headerConstruct(JSON::Object::Ptr obj, ApiFileOutputStream &stream, string expandedName, string keyName,
                             bool previousArray);
        void headerConstructorConstruct(JSON::Object::Ptr obj, ApiFileOutputStream &stream, string expandedName,
                                        string keyName, bool previousArray, bool &first);
        void cppConstruct(JSON::Object::Ptr obj, ApiFileOutputStream &stream, expansionstringstream expandedName,
                          string keyName, UInt32 objIndex, bool previousArray);
        string name;
        JSON::Object::Ptr rootObj;
    };

} // namespace trader
