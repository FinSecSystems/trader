project "gencode"
	location "%{wks.location}/tmp/projects"
	targetdir "%{wks.location}"
	targetname  "%{wks.name}.sln"
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
			"$(SolutionDir)tools\\bin\\premake\\premake5.exe --file=$(SolutionDir)premake5.lua vs2015"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
			"$(SolutionDir)tools\\bin\\premake\\premake5.exe --file=$(SolutionDir)premake5.lua vs2015"
		}

	filter { "action:vs2017", "system:windows" }
		files {
			"%{pocoPathVS2017}lib/native/include/**.h"
		}
		buildcommands {
			"$(SolutionDir)tools\\bin\\premake\\premake5.exe --file=$(SolutionDir)premake5.lua vs2017"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
			"$(SolutionDir)tools\\bin\\premake\\premake5.exe --file=$(SolutionDir)premake5.lua vs2017"
		}

	filter { "system:windows" }
---		toolset "v140"
		files {
			"%{gtestPath}lib/native/include/**.h"			
		}
		cleancommands {
			"{RMDIR} $(SolutionDir)*.vcxproj*",
			"{RMDIR} $(SolutionDir)*.sln*",
		}
