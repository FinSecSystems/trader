@echo off

pushd %~dp0..\deps\poco
buildwin 150 clean shared both Win32 samples tests devenv
rem copy /s /e /y bin\Release\vswhere.exe ..\..\bin\vswhere\.
popd
popd