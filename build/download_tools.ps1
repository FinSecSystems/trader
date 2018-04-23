Write-Host "Fetching latest nuget client binary..."
New-Item ..\tools\bin\nuget -itemtype directory
#Invoke-WebRequest -Uri "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe" -OutFile "..\tools\bin\nuget\nuget.exe"
Write-Host "Nuget downloaded!"

$Wcl=New-Object System.Net.WebClient
$Creds=Get-Credential
$Wcl.Proxy.Credentials=$Creds

New-Item ..\tools\bin\premake -itemtype directory
Invoke-WebRequest "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha12/premake-5.0.0-alpha12-windows.zip" -Out "..\tmp\premake.zip"
Write-Host "Premake downloaded!"