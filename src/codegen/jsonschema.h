#pragma once
#include "stdafx.h"
#include "endpoint.h"
#include "fileoutputstream.h"

namespace trader
{

    using namespace Poco;
    using namespace std;

    class JsonSchema : public SingletonHolder< JsonSchema >
    {
      public:
        void process(const string &_namespace, const string &_inputDir, const string &outputdirectory);

        static JsonSchema instance;
    };

} // namespace trader
