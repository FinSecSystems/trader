@echo off
pushd %~dp0\..
title Trader

REM Detect 32/64 bit windows
if exist "%SYSTEMDRIVE%\Program Files (x86)\" (
set SYS_ARCH=64
) else (
set SYS_ARCH=32
)

set TRADER_ROOT=%CD%
set PATH=%CD%\bin;%CD%\tools\bin;%PATH%
set PATH=%CD%\tools\bin;%PATH%
set PATH=%CD%\tools\cmake\bin;%PATH%
set PATH=%CD%\tools\nvm;%PATH%
rem echo %WindowsSdkDir%
rem echo %WindowsSDKLibVersion%

for /f "usebackq tokens=1* delims=: " %%i in (`%CD%\tools\bin\vswhere\vswhere -latest -requires Microsoft.Component.MSBuild`) do (
  if /i "%%i"=="installationPath" set LatestVS=%%j
)

REM Setup Visual Studio Environment
doskey devenv=devenv.exe /useenv $*
setlocal enabledelayedexpansion
IF NOT "%LatestVS%"=="" (
	set "VS150COMNTOOLS=%LatestVS%\Common7\Tools\"
	call "%LatestVS%\VC\Auxiliary\Build\vcvarsall.bat" x64

) ELSE (
	IF NOT "%VS140COMNTOOLS%"=="" (
		ECHO Visual Studio 2015
		call "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
	) ELSE (
		ECHO Visual Studio 2012
		call "%VS110COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
	)
)
set PATH=!WindowsSdkDir!bin\!WindowsSDKLibVersion!x64\;!PATH!
%comspec% /k
popd
