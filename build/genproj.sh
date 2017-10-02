#!/bin/bash

pushd $(dirname $0)
cd ..
./tools/bin/premake/premake5 gmake $1
popd
