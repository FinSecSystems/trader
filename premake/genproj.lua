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
		"%{wks.location}/*.config"
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

	filter { "system:windows" }
		files {
			"packages.config"			
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

	filter { "platforms:Win64", "system:windows" }
		files {
			"%{gtestPath}lib/native/include/**.h"
		}

	filter { "platforms:Win64", "action:vs2015", "system:windows" }
		files {
			"%{pocoPathVS2015}lib/native/include/**.h"
		}

	filter { "platforms:Win64", "action:vs2017", "system:windows" }
		files {
			"%{pocoPathVS2017}lib/native/include/**.h"
		}
