Write-Host "Fetching latest nuget client binary..."
New-Item ..\tools\bin\nuget -itemtype directory -ErrorAction SilentlyContinue 
Invoke-WebRequest -Uri "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe" -OutFile "..\tools\bin\nuget\nuget.exe"
Write-Host "Nuget Deployed"

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$repo = "premake/premake-core"
$file = "premake.zip"
$exename = "premake5.exe"
$destinationdir = "..\tools\bin\premake"

New-Item $destinationdir -itemtype directory -ErrorAction SilentlyContinue 

$releases = "https://api.github.com/repos/$repo/releases"

Write-Host Determining latest release
$tag = (Invoke-WebRequest $releases | ConvertFrom-Json)[0].tag_name.Substring(1)

$name = $file.Split(".")[0]
$zip = "$name-$tag-windows.zip"
$dir = "$name-$tag"
$zipfile = "..\tmp\$name-$tag-windows.zip"

$download = "https://github.com/$repo/releases/download/v$tag/$zip"

Write-Host Dowloading latest release
Write-Host $download
Invoke-WebRequest $download -Out $zipfile

Write-Host Extracting release files
Expand-Archive $zipfile -Force -DestinationPath "..\tmp"

# Cleaning up target dir
Remove-Item $destinationdir\$exename -Force -ErrorAction SilentlyContinue 

# Moving from temp dir to target dir
Move-Item ..\tmp\$exename -Destination $destinationdir\$exename -Force

# Removing temp files
Remove-Item $zipfile -Force

