project "databases"
	dependson { 
		"codegen"
	}
	kind		"Utility"
	targetdir	"%{wks.location}/tmp/%{cfg.platform}/codegen"
	targetname	"fybdatabase.h"
	files
	{
        "%{wks.location}/data/databases/**.json"
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

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/databases -o:tmp/%{cfg.platform}/codegen -n:trader -t:databaseschema"
		}
		rebuildcommands {
			"{RMDIR} tmp/%{cfg.platform}/codegen/**database.*",
			"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/databases -o:tmp/%{cfg.platform}/codegen -n:trader -t:databaseschema"
		}
		cleancommands {
			"{RMDIR} tmp/%{cfg.platform}/codegen/**database.*",
		}
