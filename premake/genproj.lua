project "genproj"
	location "%{wks.location}/tmp/projects"
	targetname  "genproj"
    kind "Makefile"
	files
	{
        "%{wks.location}/*.lua",
		"%{wks.location}/*.md",
		"%{wks.location}/*.txt",
		"%{wks.location}/premake/**",
		"%{wks.location}/*.config",
		"%{wks.location}/*.yml"
	}

	filter { "system:linux" }
		buildcommands {
			"%{wks.location}/tools/bin/premake/premake5 gmake"
		}

		rebuildcommands {
			"{RMDIR} %{wks.location}/Makefile",
			"{RMDIR} %{wks.location}/*.make",
			"%{wks.location}/tools/bin/premake/premake5 gmake"
		}

		cleancommands {
			"{RMDIR} %{wks.location}Makefile",
			"{RMDIR} %{wks.location}*.make"
		}

	filter { "action:vs2015", "system:windows" }
		files {
			"%{pocoPathVS2015}lib/native/include/**.h"
		}
		buildcommands {
			"%{wks.location}tools\\bin\\nuget\\nuget.exe install %{pocoPackageVS2015} -OutputDirectory %{wks.location}\\packages"
		}

	filter { "action:vs2017", "system:windows" }
		files {
			"%{pocoPathVS2017}lib/native/include/**.h"
		}
		buildcommands {
			"%{wks.location}tools\\bin\\nuget\\nuget.exe install %{pocoPackageVS2017} -OutputDirectory %{wks.location}\\packages"
		}

	filter { "system:windows" }
		files {
			"%{gtestPath}lib/native/include/**.h"			
		}
		buildcommands {
			"%{wks.location}tools\\bin\\nuget\\nuget.exe install %{gTestPackage} -OutputDirectory %{wks.location}\\packages",
			"$(SolutionDir)build\\genproj.cmd"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
			"$(SolutionDir)build\\genproj.cmd"
		}
		cleancommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
		}
