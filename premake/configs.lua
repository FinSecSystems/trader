project "configs"
	location "%{wks.location}/tmp/projects"
	targetname "fybconfig.h"
	dependson { 
		"codegen"
	}
	kind "Utility"
	targetdir "%{wks.location}/tmp/%{cfg.platform}/codegen"
	files
	{
		"%{wks.location}/data/configs/**.json"
	}

	filter { "platforms:Win64", "system:windows" }
		prebuildcommands {
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:jsonschema"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:jsonschema"
		}
		cleancommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		}

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/configs -o:tmp/%{cfg.platform}/codegen -n:trader -t:jsonschema"
		}
		rebuildcommands {
			"{RMDIR} tmp/%{cfg.platform}/codegen/**config.*",
			"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/configs -o:tmp/%{cfg.platform}/codegen -n:trader -t:jsonschema"
		}
		cleancommands {
			"{RMDIR} tmp/%{cfg.platform}/codegen/**config.*",
		}
