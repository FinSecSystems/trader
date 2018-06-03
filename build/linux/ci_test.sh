#!/bin/bash

pushd $(dirname $0)
cd ../..
make -f generators.make verbose=1 clean
make -f trader.make verbose=1 clean
build/linux/deploy_tools.sh && build/linux/genproj.sh && make -f generators.make verbose=1 && make -f trader.make verbose=1
popd
