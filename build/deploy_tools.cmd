@echo off
pushd "%~dp0"

call powershell -ExecutionPolicy Bypass -File .\deploy_tools.ps1

popd
pause