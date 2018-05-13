#pragma once

#include "endpoint.h"
#include "fileoutputstream.h"
#include "objectschemadefinition.h"

namespace trader
{

    struct Config
    {
        void read(JSON::Object::Ptr obj)
        {
            baseUrl = obj->getValue< string >("baseurl");
            Dynamic::Var useConfigVar = obj->get("useConfig");
            if (!useConfigVar.isEmpty())
            {
                useConfig = useConfigVar.convert< bool >();
            }
        }

        Config()
            : useConfig(false)
        {
        }

        string baseUrl;
        string outputDir;
        string nameSpace;
        string apiName;
        string headerFileName;
        string cppFileName;
        bool useConfig;
        typedef std::map< string, ObjectSchemaDefinition > SchemaDefMap;
        SchemaDefMap schemaDefinitions;
    };
} // namespace trader
