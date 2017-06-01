@echo off

pushd %~dp0..\src\vswhere
devenv vswhere.sln /build "Release|x86"
xcopy /s /e /y bin\Release\vswhere.exe ..\..\bin\vswhere\.
popd