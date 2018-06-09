project "apis"
	location "%{wks.location}/tmp/projects"
	targetname "fybapi.h"
	dependson { 
		"codegen"
	}
	targetdir "%{wks.location}/tmp/%{cfg.platform}/codegen/"
	kind "Utility"
	files
	{
		"%{wks.location}/data/apis/**.json"
	}

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"LD_LIBRARY_PATH=%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/:$$LD_LIBRARY_PATH %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:%{wks.location}/data/apis -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:hyperschema"
		}		
		rebuildcommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**api.*",
			"LD_LIBRARY_PATH=%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/:$$LD_LIBRARY_PATH %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:%{wks.location}/data/apis -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:hyperschema"
		}
		cleancommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**api.*",
		}		
		
	filter { "platforms:Win64", "system:windows" }
		prebuildcommands {
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:hyperschema"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:hyperschema"
		}
		cleancommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		}
