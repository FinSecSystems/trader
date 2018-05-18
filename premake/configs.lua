project "configs"
	location "%{wks.location}/tmp/projects"
	targetname "%{wks.location}/tmp/%{cfg.platform}/codegen/fybconfig.h"
	dependson { 
		"codegen"
	}
	kind "Utility"
	targetdir "%{wks.location}/tmp/%{cfg.platform}/codegen"
	files
	{
		"%{wks.location}/data/configs/**.json"
	}

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"LD_LIBRARY_PATH=%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/:$$LD_LIBRARY_PATH %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:%{wks.location}/data/configs -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:jsonschema"
		}
		rebuildcommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**config.*",
			"LD_LIBRARY_PATH=%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/:$$LD_LIBRARY_PATH %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:%{wks.location}/data/configs -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:jsonschema"
		}
		cleancommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**config.*",
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
