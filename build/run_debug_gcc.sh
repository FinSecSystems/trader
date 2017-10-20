#!/bin/bash
pushd $(dirname $0)
cd ../bin/Linux64-gcc/debug
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../deps/poco/lib/Linux/x86_64 ./$@
popd
