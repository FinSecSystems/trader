@echo off

pushd $(dirname $0)
cd ../deps/poco
export POCO_VERBOSE=1
export POCO_CONFIG=Linux-clang
export OMIT="Data/ODBC Data/MySQL MongoDB Redis PDF CppParser Data/PostgreSQL Data/MySQL"
make
popd
