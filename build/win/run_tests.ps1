$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Push-Location $dir
[Environment]::CurrentDirectory = $dir

#[Environment]::SetEnvironmentVariable("configuration", "debug-static")

Get-ChildItem "..\..\bin\Win64\$($env:configuration)" -Filter *test.exe | 
Foreach-Object {
	$testName = $_
	$fullExePath = $_.FullName
	$exeName = $_.BaseName
	$testFileName = '..\..\' + $testName + '.xml'
	$testLogFileName = '..\..\bin\Win64\' + $env:configuration + '\' + $exeName + '.log.txt'

	#& "$fullExePath" --gtest_output=xml:$testFileName
	
	$src=[System.IO.Path]::GetFullPath((Join-Path $dir '..\..\src'))
	$reportFileName = '..\..\bin\Win64\' + $env:configuration + '\' + $exeName + '.cov'
	$report=[System.IO.Path]::GetFullPath((Join-Path $dir $reportFileName))
	$workingDirPath='..\..\bin\Win64\' + $env:configuration
	$working_dir=[System.IO.Path]::GetFullPath((Join-Path $dir $workingDirPath))
	$testFileDir = '..\..\bin\Win64\' + $env:configuration + '\' + $testFileName
	$test_file_name=[System.IO.Path]::GetFullPath((Join-Path $dir $testFileDir))
	& "..\..\tools\bin\OpenCppCoverage\OpenCppCoverage.exe" --sources=$src --export_type=binary:$report --working_dir=$working_dir --excluded_modules=c:\windows\system32* -- $fullExePath --gtest_output=xml:$testFileName
	#Get-Content $testLogFileName
	
	#Upload test reports
	(new-object net.webclient).UploadFile("https://ci.appveyor.com/api/testresults/junit/$($env:APPVEYOR_JOB_ID)", (Resolve-Path $test_file_name) )
}

# Combine reports
$global:inputfiles = $null
Get-ChildItem "..\..\bin\Win64\$($env:configuration)" -Filter *test.exe | 
Foreach-Object {
	$exeName = $_.BaseName
	$reportFileName = '..\..\bin\Win64\' + $env:configuration + '\' + $exeName + '.cov'
	$report=[System.IO.Path]::GetFullPath((Join-Path $dir $reportFileName))
	$global:inputfiles = $global:inputfiles + " --input_coverage=" + $report
}

$reportFileName = '..\..\code_coverage_report.xml'
$report=[System.IO.Path]::GetFullPath((Join-Path $dir $reportFileName))
$src=[System.IO.Path]::GetFullPath((Join-Path $dir '..\..\src'))
$binaryName = '..\..\bin\Win64\' + $env:configuration + '\sample_app_test.exe'
$binary_name = [System.IO.Path]::GetFullPath((Join-Path $dir $binaryName))
$workingDirPath='..\..\bin\Win64\' + $env:configuration
$working_dir=[System.IO.Path]::GetFullPath((Join-Path $dir $workingDirPath))
Write-Host "..\..\tools\bin\OpenCppCoverage\OpenCppCoverage.exe" $global:inputfiles --sources=$src --export_type=cobertura:$report --working_dir=$working_dir -- $binary_name
$Prms = $global:inputfiles.Split(" ")
& "..\..\tools\bin\OpenCppCoverage\OpenCppCoverage.exe" --sources=$src --export_type=cobertura:$report --working_dir=$working_dir $Prms -- $binary_name

Pop-Location
[Environment]::CurrentDirectory = $PWD

