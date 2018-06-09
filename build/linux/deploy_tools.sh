#!/bin/bash
pushd $(dirname $0)
pwd
#apt-get install -qq -y autoconf gcc clang premake libpoco* jq python-pip
cat ../../deb_dependencies.txt | xargs apt-get install -qq -y
mkdir -p ../../tmp
mkdir -p ../../tmp/projects

export CURL_LOGIN=
export WGET_LOGIN=
if [ -n "$GITHUB_USERNAME" ]&& [ -n "$GITHUB_PASSWORD" ]
then
echo Using GitHub Credentials
export CURL_LOGIN="-u $GITHUB_USERNAME:$GITHUB_PASSWORD"
export WGET_LOGIN="--user $GITHUB_USERNAME --password $GITHUB_PASSWORD"
fi

if [ -e ../../tools/bin/premake/premake5 ]
then
	echo "Premake found..."
else
	echo "Installing Premake..."
	wget $WGET_LOGIN -O ../../tmp/premake.tar.gz `curl $CURL_LOGIN -s https://api.github.com/repos/premake/premake-core/releases | jq -r ".[0].assets[] | select(.name | test(\"linux\")) | .browser_download_url"`
	tar zxf ../../tmp/premake.tar.gz -C ../../tools/bin/premake
	chmod 777 ../../tools/bin/premake
fi

pip install -r ../../requirements.txt
conan remote add conan-poco https://api.bintray.com/conan/finsecsystem/finsec.pocoproject
if [ -n "$CC_VER" ]
then
	echo Setiing up for gcc-$CC_VER
	apt-get install -qq -y gcc-$CC_VER g++-$CC_VER
	pwd
	conan install -if ../../tmp/. ../../. -s compiler.version=$CC_VER -s compiler.libcxx=libstdc++ -s build_type=Release --no-imports -o *:shared=False && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-release-static/
	conan install -if ../../tmp/. ../../. -s compiler.version=$CC_VER -s compiler.libcxx=libstdc++ -s build_type=Release --no-imports -o *:shared=True  && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-release-shared/
	conan install -if ../../tmp/. ../../. -s compiler.version=$CC_VER -s compiler.libcxx=libstdc++ -s build_type=Debug   --no-imports -o *:shared=False && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-debug-static/
	conan install -if ../../tmp/. ../../. -s compiler.version=$CC_VER -s compiler.libcxx=libstdc++ -s build_type=Debug   --no-imports -o *:shared=True  && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-debug-shared/
else
	conan install -if ../../tmp/. ../../. -s compiler.libcxx=libstdc++ -s build_type=Release --no-imports -o *:shared=False && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-release-static/
	conan install -if ../../tmp/. ../../. -s compiler.libcxx=libstdc++ -s build_type=Release --no-imports -o *:shared=True  && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-release-shared/
	conan install -if ../../tmp/. ../../. -s compiler.libcxx=libstdc++ -s build_type=Debug   --no-imports -o *:shared=False && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-debug-static/
	conan install -if ../../tmp/. ../../. -s compiler.libcxx=libstdc++ -s build_type=Debug   --no-imports -o *:shared=True  && conan imports -if ../../tmp/. ../../. -imf ../../packages/finsec.poco-linux-gcc.1.9.0-debug-shared/
fi
popd

