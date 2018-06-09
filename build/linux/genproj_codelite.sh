#!/bin/bash

pushd $(dirname $0)
cd ../..
./tools/bin/premake/premake5 finseccodelite $1
popd
