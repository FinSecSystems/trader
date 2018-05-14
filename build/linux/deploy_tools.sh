#!/bin/bash
pushd $(dirname $0)
#apt-get install -y autoconf gcc clang premake libpoco* jq
if [ -e ../../tools/bin/premake/premake5 ]
then
	echo "Premake found..."
else
	echo "Installing Premake..."
	wget `curl -s https://api.github.com/repos/premake/premake-core/releases | jq -r ".[0].assets[] | select(.name | test(\"linux\")) | .browser_download_url"` -O ../../tmp/premake.tar.gz
	tar zxf ../../tmp/premake.tar.gz -C ../../tools/bin/premake
fi
popd

