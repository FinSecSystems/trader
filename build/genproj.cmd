@echo off
pushd %~dp0
call _lib\_setup_env.cmd
pushd %~dp0\..
echo Premake building for %PREMAKE_TOOLCHAIN%
tools\bin\premake\premake5.exe %PREMAKE_TOOLCHAIN%
popd
popd