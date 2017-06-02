@echo off

pushd %~dp0..\deps\intel_se_api
del CMakeCache.txt
..\..\tools\bin\cmake\bin\cmake.exe . -G"Visual Studio 15 Win64" -DARCH_64=1
devenv IntelSEAPI.sln /build "Release|x64"
rem copy /s /e /y bin\Release\vswhere.exe ..\..\bin\vswhere\.
popd
popd