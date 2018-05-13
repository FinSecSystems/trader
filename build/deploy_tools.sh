#!/bin/bash
pushd $(dirname $0)
apt-get install -y autoconf gcc clang premake libpoco*
popd
