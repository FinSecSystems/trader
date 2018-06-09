$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Push-Location $dir
[Environment]::CurrentDirectory = $dir

$secure_tool_dir = "..\..\tools\bin\appveyor-tools"

if(![System.IO.Directory]::Exists($secure_tool_dir)){
	Write-Host "Install Secure Client Tools"
	Remove-Item $secure_tool_dir -Force -ErrorAction SilentlyContinue -Recurse
	Push-Location ..\..\tools\bin
	iex ((New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/appveyor/secure-file/master/install.ps1'))
	Pop-Location
}

Get-ChildItem "..\..\configs" | 
Foreach-Object {
	$testName = $_
	$fullExePath = $_.FullName
	$exeName = $_.BaseName
	$testFileName = '..\..\bin\' + $exeName
	Write-Host "Generating config $testFileName"
	& "$secure_tool_dir\secure-file" -decrypt $fullExePath -secret $env:my_secret -out $testFileName
}

Pop-Location
[Environment]::CurrentDirectory = $PWD

