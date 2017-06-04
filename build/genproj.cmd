@echo off
pushd %~dp0\..
tools\bin\premake\premake5 vs2017
popd