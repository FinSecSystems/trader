project "genproj"
	toolset "v140"
    kind "Makefile"
	location "%{wks.location}/tmp/projects"
	targetdir "%{wks.location}"
	targetname  "%{wks.name}.sln"
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

	filter { "action:vs2017", "system:windows" }
		files {
			"%{pocoPathVS2017}lib/native/include/**.h"
		}

	filter { "system:windows" }
		files {
			"%{gtestPath}lib/native/include/**.h"			
		}
		buildcommands {
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
