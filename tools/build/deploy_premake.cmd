@echo off

pushd %~dp0..\src\premake-core
..\..\bin\premake\premake5 vs2017
..\..\bin\premake\premake5 embed
devenv Premake5.sln /build "Release|Win32"
xcopy /s /e /y bin\Release\premake5.exe ..\..\bin\premake\.
popd