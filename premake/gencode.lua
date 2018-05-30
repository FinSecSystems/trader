project "gencode"
	location "%{wks.location}/tmp/projects"
	targetdir "%{wks.location}"
    kind "Makefile"
	dependson {
		"apis",
		"configs",
		"databases",
		"interface"	
	}
	files
	{
        "%{wks.location}/*.lua",
		"%{wks.location}/*.md",
		"%{wks.location}/*.txt",
		"%{wks.location}/premake/**",
		"%{wks.location}/*.config",
		"%{wks.location}/*.yml",
		"%{wks.location}/build/**.cmd",
		"%{wks.location}/build/**.ps1"
	}

	filter { "system:linux" }
		targetname  "%{wks.name}.make"
		buildcommands {
			"pwd",
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

	filter { "action:vs2017", "system:windows" }
		files {
			"%{pocoPathVS2017}lib/native/include/**.h"
		}

	filter { "system:windows" }
		toolset "v140"
		targetname  "%{wks.name}.sln"
		files {
			"%{gtestPath}lib/native/include/**.h"			
		}
		buildcommands {
			"$(SolutionDir)build\\win\\genproj.cmd"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
			"$(SolutionDir)build\\win\\genproj.cmd"
		}
		cleancommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
		}
