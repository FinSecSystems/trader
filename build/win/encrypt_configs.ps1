 param (
    [string]$password = $( Read-Host "Input password, please" )
 )

$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Push-Location $dir
[Environment]::CurrentDirectory = $dir

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

Write-Host "Setup directories"
New-Item "..\..\configs" -itemtype directory -ErrorAction SilentlyContinue

$secure_tool_dir = "..\..\tools\bin\appveyor-tools"

if(![System.IO.Directory]::Exists($secure_tool_dir)){
	Write-Host "Install Secure Client Tools"
	Remove-Item $secure_tool_dir -Force -ErrorAction SilentlyContinue -Recurse
	Push-Location ..\..\tools\bin
	iex ((New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/appveyor/secure-file/master/install.ps1'))
	Pop-Location
}

Get-ChildItem "..\..\bin\Win64" -Filter *.properties | 
Foreach-Object {
	Write-Host "Encrypting $_ ..."
	& "$secure_tool_dir\secure-file" -encrypt $_.Fullname -secret $password 
}

Get-ChildItem "..\..\bin\Win64" -Filter *.json | 
Foreach-Object {
	Write-Host "Encrypting $_ ..."
	& "$secure_tool_dir\secure-file" -encrypt $_.Fullname -secret $password
}

Move-Item "..\..\bin\Win64\*.enc" -Destination "..\..\configs" -Force -ErrorAction SilentlyContinue

Write-Host "Encryption Complete."


Pop-Location
[Environment]::CurrentDirectory = $PWD

