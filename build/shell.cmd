@echo off
pushd %~dp0\..
title Trader

REM Detect 32/64 bit windows
if exist "%SYSTEMDRIVE%\Program Files (x86)\" (
set SYS_ARCH=64
) else (
set SYS_ARCH=32
)

set CATALYST_ROOT=%CD%
set PATH=%CD%\bin;%CD%\tools\bin;%PATH%
set PATH=%CD%\tools\bin;%PATH%
set PATH=%CD%\tools\cmake\bin;%PATH%
set PATH=%CD%\tools\nvm;%PATH%

for /f "usebackq tokens=1* delims=: " %%i in (`%CD%\tools\bin\vswhere\vswhere -latest -requires Microsoft.Component.MSBuild`) do (
  if /i "%%i"=="installationPath" set LatestVS=%%j
)

REM Setup Visual Studio Environment
doskey devenv=devenv.exe /useenv $*

IF NOT "%LatestVS%"=="" (
	%comspec% /k "%LatestVS%\Common7\Tools\VsDevCmd.bat"
) ELSE (
	IF NOT "%VS140COMNTOOLS%"=="" (
		ECHO Visual Studio 2015
		rem %comspec% /k "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
	) ELSE (
		ECHO Visual Studio 2012
		rem %comspec% /k "%VS110COMNTOOLS%\..\..\VC\vcvarsall.bat" x64
	)
)
popd
