#pragma once
#include "stdafx.h"

#include "endpoint.h"
#include "fileoutputstream.h"

namespace trader
{

    using namespace Poco;
    using namespace std;

    class HyperSchema : public SingletonHolder< HyperSchema >
    {
      public:
        void process(const string &_namespace, const string &_inputDir, const string &outputdirectory);

        static HyperSchema instance;
    };

} // namespace trader
