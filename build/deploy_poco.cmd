@echo off

pushd %~dp0..\deps\poco
call buildwin 150 build shared both x64 samples tests devenv noenv
popd