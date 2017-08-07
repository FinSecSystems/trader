@echo off
pushd %~dp0
call _lib\_setup_env.cmd
pushd %~dp0..\deps\intel_se_api
del CMakeCache.txt
..\..\tools\bin\cmake\bin\cmake.exe . -G"%CMAKE_TOOLCHAIN%" -DARCH_64=1
devenv IntelSEAPI.sln /build "Release|x64"
rem copy /s /e /y bin\Release\vswhere.exe ..\..\bin\vswhere\.
popd
popd
popd