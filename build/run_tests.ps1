$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Push-Location $dir
[Environment]::CurrentDirectory = $dir

$configuration = "debug-static"

Get-ChildItem "..\bin\Win64\$($env:configuration)" -Filter *test.exe | 
Foreach-Object {
	$testName = $_
	$fullExePath = $_.FullName
	$exeName = $_.BaseName
	$testFileName = '..\' + $testName + '.xml'

	& "$fullExePath" --gtest_output=xml:$testFileName

	(new-object net.webclient).UploadFile("https://ci.appveyor.com/api/testresults/junit/$($env:APPVEYOR_JOB_ID)", (Resolve-Path $testFileName) )
}

Pop-Location
[Environment]::CurrentDirectory = $PWD

