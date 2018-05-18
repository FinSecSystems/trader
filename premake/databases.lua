project "databases"
	location "%{wks.location}/tmp/projects"
	dependson { 
		"codegen"
	}
	kind		"Utility"
	targetdir	"%{wks.location}/tmp/%{cfg.platform}/codegen"
	targetname	"%{wks.location}/tmp/%{cfg.platform}/codegen/fybdatabase.h"
	files
	{
        "%{wks.location}/data/databases/**.json"
	}

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:%{wks.location}/data/databases -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:databaseschema"
		}
		rebuildcommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**database.*",
			"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:%{wks.location}/data/databases -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:databaseschema"
		}
		cleancommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**database.*",
		}

	filter { "platforms:Win64", "system:windows" }
		prebuildcommands {
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\databases /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:databaseschema"
		}

		rebuildcommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\databases /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:databaseschema"
		}

		cleancommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		}