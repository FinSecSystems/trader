$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Push-Location $dir
[Environment]::CurrentDirectory = $dir

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

#vswhere
$repo = "Microsoft/vswhere"
$exename = "vswhere.exe"
$destinationdir = "..\tools\bin\vswhere"

Write-Host "Setup directories"
New-Item "..\tmp" -itemtype directory -ErrorAction SilentlyContinue
New-Item "..\tools" -itemtype directory -ErrorAction SilentlyContinue
New-Item "..\tools\bin" -itemtype directory -ErrorAction SilentlyContinue

Write-Host "Installing VSWhere"
$releases = "https://api.github.com/repos/$repo/releases"
$url = (Invoke-WebRequest $releases | ConvertFrom-Json)[0].assets[0].browser_download_url
$download = "https://github.com/$repo/releases/download/$tag/$exename"
New-Item $destinationdir -itemtype directory -ErrorAction SilentlyContinue 
Write-Host $download
Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 
Invoke-WebRequest $url -Out $destinationdir\$exename

# Nuget
Write-Host "Installing Nuget"
New-Item ..\tools\bin\nuget -itemtype directory -ErrorAction SilentlyContinue 
Invoke-WebRequest -Uri "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe" -OutFile "..\tools\bin\nuget\nuget.exe"
Write-Host "Nuget Deployed"

#Premake
$repo = "premake/premake-core"
$file = "premake.zip"
$exename = "premake5.exe"
$destinationdir = "..\tools\bin\premake"

Write-Host "Installing Premake"
$releases = "https://api.github.com/repos/$repo/releases"
$tag = (Invoke-WebRequest $releases | ConvertFrom-Json)[0].tag_name.Substring(1)
$name = $file.Split(".")[0]
$zip = "$name-$tag-windows.zip"
$dir = "$name-$tag"
$zipfile = "..\tmp\$name-$tag-windows.zip"
$download = "https://github.com/$repo/releases/download/v$tag/$zip"
New-Item $destinationdir -itemtype directory -ErrorAction SilentlyContinue
Write-Host $download
Invoke-WebRequest $download -Out $zipfile
Expand-Archive $zipfile -Force -DestinationPath "..\tmp"
Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 
Move-Item ..\tmp\$exename -Destination $destinationdir\$exename -Force
Remove-Item $zipfile -Force

Pop-Location
[Environment]::CurrentDirectory = $PWD
