@echo off
pushd %~dp0\..\..

for /f "usebackq tokens=1* delims=: " %%i in (`%CD%\tools\bin\vswhere\vswhere -latest -requires Microsoft.Component.MSBuild`) do (
  if /i "%%i"=="installationPath" set LatestVS=%%j
)

REM Setup Visual Studio Environment
REM doskey devenv=devenv.exe /useenv $*

IF NOT "%LatestVS%"=="" (
	set PREMAKE_TOOLCHAIN=vs2017
	set POCO_TOOLCHAIN=150
	set POCO_TOOLCHAIN_ENV=
	set POCO_TOOLCHAIN_BUILD=devenv
	set CMAKE_TOOLCHAIN=Visual Studio 15 Win64
	set CL=/MP
) ELSE (
	IF NOT "%VS140COMNTOOLS%"=="" (
		ECHO Visual Studio 2015
		set PREMAKE_TOOLCHAIN=vs2015
		set POCO_TOOLCHAIN=140
		set POCO_TOOLCHAIN_ENV=
		set POCO_TOOLCHAIN_BUILD=msbuild
		set CMAKE_TOOLCHAIN=Visual Studio 14 Win64
		set CL=/MP
	) ELSE (
		ECHO Visual Studio 2012
		set PREMAKE_TOOLCHAIN=vs2012
		set POCO_TOOLCHAIN=110
		set POCO_TOOLCHAIN_ENV=
		set POCO_TOOLCHAIN_BUILD=msbuild
		set CMAKE_TOOLCHAIN=Visual Studio 11 Win64
		set CL=/MP
	)
)
popd
