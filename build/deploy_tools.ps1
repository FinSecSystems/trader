$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Push-Location $dir
[Environment]::CurrentDirectory = $dir

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

Write-Host "Setup directories"
New-Item "..\tmp" -itemtype directory -ErrorAction SilentlyContinue
New-Item "..\tools" -itemtype directory -ErrorAction SilentlyContinue
New-Item "..\tools\bin" -itemtype directory -ErrorAction SilentlyContinue
New-Item "..\packages" -itemtype directory -ErrorAction SilentlyContinue

#Set Github Credentials

function Get-BasicAuthCreds {
    param([string]$Username,[string]$Password)
    $AuthString = "{0}:{1}" -f $Username,$Password
    $AuthBytes  = [System.Text.Encoding]::Ascii.GetBytes($AuthString)
    return [Convert]::ToBase64String($AuthBytes)
}

$global:headers = $null
if (Test-Path env:my_github_username) {
	if (Test-Path env:my_github_password) {
		$BasicCreds = Get-BasicAuthCreds -Username $env:my_github_username -Password $env:my_github_password
		$global:headers = @{"Authorization"="Basic $BasicCreds"}
		Write-Host "Retrieved Credentials"
	}
}

#opencppcoverage
$opencppcoverageDir = "$dir\..\tools\bin\OpenCppCoverage\"
if(![System.IO.Directory]::Exists($opencppcoverageDir)){
	Write-Host "Installing OpenCppCoverage $opencppcoverageDir"
	$repo = "OpenCppCoverage/OpenCppCoverage"
	$exename = "OpenCppCoverageSetup-x64-0.9.7.0.exe"
	$destinationdir = "..\tmp"
	$releases = "https://api.github.com/repos/$repo/releases"
	$url = (Invoke-WebRequest $releases -Headers $headers | ConvertFrom-Json)[0].assets[0].browser_download_url
	$download = "https://github.com/$repo/releases/download/$tag/$exename"
	Write-Host $download
	Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 
	Invoke-WebRequest $url -Out $destinationdir\$exename -Headers $headers
	& "$destinationdir\$exename" /VERYSILENT /DIR="$opencppcoverageDir"
}

#intelseapi
$intelseapiDir = "$dir\..\packages\IntelSEAPI-Windows\"
if(![System.IO.Directory]::Exists($intelseapiDir)){
	Write-Host "Installing IntelSEAPI $intelseapiDir"
	$repo = "intel/IntelSEAPI"
	$exename = "IntelSEAPI-Windows.exe"
	$destinationdir = "..\tmp"
	$releases = "https://api.github.com/repos/$repo/releases"
	$url = (Invoke-WebRequest $releases -Headers $headers | ConvertFrom-Json)[0].assets[2].browser_download_url
	$download = "https://github.com/$repo/releases/download/$tag/$exename"
	Write-Host $download
	Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 
	Invoke-WebRequest $url -Out $destinationdir\$exename -Headers $headers
	& "$destinationdir\$exename" /S  /D=$intelseapiDir
}

#vswhere
$exename = "vswhere.exe"
$destinationdir = "..\tools\bin\vswhere"
if(![System.IO.File]::Exists("$destinationdir\$exename")){
	Write-Host "Installing VSWhere"
	$repo = "Microsoft/vswhere"
	$releases = "https://api.github.com/repos/$repo/releases"
	$url = (Invoke-WebRequest $releases -Headers $headers | ConvertFrom-Json)[0].assets[0].browser_download_url
	$download = "https://github.com/$repo/releases/download/$tag/$exename"
	New-Item $destinationdir -itemtype directory -ErrorAction SilentlyContinue 
	Write-Host $download 
	Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 
	Invoke-WebRequest $url -Out $destinationdir\$exename -Headers $headers
}

# Nuget
$nugetFile = "..\tools\bin\nuget\nuget.exe"
if(![System.IO.File]::Exists("$nugetFile")){
	Write-Host "Installing Nuget"
	New-Item ..\tools\bin\nuget -itemtype directory -ErrorAction SilentlyContinue 
	Invoke-WebRequest -Uri "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe" -OutFile $nugetFile
	Write-Host "Nuget Deployed"
}

#Premake
$exename = "premake5.exe"
$destinationdir = "..\tools\bin\premake"
if(![System.IO.File]::Exists("$destinationdir\$exename")){
	Write-Host "Installing Premake"
	$repo = "premake/premake-core"
	$file = "premake.zip"
	$releases = "https://api.github.com/repos/$repo/releases"
	$tag = (Invoke-WebRequest $releases -Headers $headers | ConvertFrom-Json)[0].tag_name.Substring(1)
	$name = $file.Split(".")[0]
	$zip = "$name-$tag-windows.zip"
	$dir = "$name-$tag"
	$zipfile = "..\tmp\$name-$tag-windows.zip"
	$download = "https://github.com/$repo/releases/download/v$tag/$zip"
	New-Item $destinationdir -itemtype directory -ErrorAction SilentlyContinue
	Write-Host $download 
	Invoke-WebRequest $download -Out $zipfile -Headers $headers
	Expand-Archive $zipfile -Force -DestinationPath "..\tmp"
	Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 
	Move-Item ..\tmp\$exename -Destination $destinationdir\$exename -Force
	Remove-Item $zipfile -Force
}

#Poco
if (Test-Path env:VS_PLATFORM_TOOLSET)
{
	if(![System.IO.Directory]::Exists("..\packages\finsec.poco-windows-$env:VS_PLATFORM_TOOLSET.1.8.0.1")) {
		& "..\tools\bin\nuget\nuget.exe" install finsec.poco-windows-$env:VS_PLATFORM_TOOLSET -OutputDirectory ..\packages
	}
}
else
{
	if(![System.IO.Directory]::Exists("..\packages\finsec.poco-windows-v140.1.8.0.1")) {
		& "..\tools\bin\nuget\nuget.exe" install finsec.poco-windows-v140 -OutputDirectory ..\packages
	}
	if(![System.IO.Directory]::Exists("..\packages\finsec.poco-windows-v141.1.8.0.1")) {
		& "..\tools\bin\nuget\nuget.exe" install finsec.poco-windows-v141 -OutputDirectory ..\packages
	}
}

#gTest
if(![System.IO.Directory]::Exists("..\packages\gtest-vc140-static-64.1.1.0")) {
	& "..\tools\bin\nuget\nuget.exe" install gtest-vc140-static-64 -OutputDirectory ..\packages
}
if(![System.IO.Directory]::Exists("..\packages\Microsoft.googletest.v140.windesktop.msvcstl.dyn.rt-dyn.1.8.0")) {
	& "..\tools\bin\nuget\nuget.exe" install Microsoft.googletest.v140.windesktop.msvcstl.dyn.rt-dyn -OutputDirectory ..\packages
}

#Visual Leak Detector
if(![System.IO.Directory]::Exists("..\packages\VisualLeakDetector.2.5.0.0")) {
	& "..\tools\bin\nuget\nuget.exe" install VisualLeakDetector -OutputDirectory ..\packages
}

Write-Host "Check packages and tools directories"
Get-ChildItem -Path "..\packages"
Get-ChildItem -Path "..\tools" –Recurse

Pop-Location
[Environment]::CurrentDirectory = $PWD

