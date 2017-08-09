@echo off
pushd %~dp0
call _lib\_setup_env.cmd
pushd %~dp0..\deps\poco
call buildwin %POCO_TOOLCHAIN% build shared both x64 samples tests %POCO_TOOLCHAIN_BUILD% %POCO_TOOLCHAIN_ENV%
popd
popd