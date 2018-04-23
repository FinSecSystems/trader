@echo off
pushd "%~dp0"

call powershell -ExecutionPolicy Bypass -File .\download_tools.ps1

popd
pause