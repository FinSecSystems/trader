@echo off
pushd "%~dp0"

call powershell -ExecutionPolicy Bypass -File .\encrypt_configs.ps1

popd
pause