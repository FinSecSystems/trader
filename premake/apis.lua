project "apis"
	targetname "fybapi.h"
	dependson { 
		"codegen"
	}
	targetdir "%{wks.location}/tmp/%{cfg.platform}/codegen"
	kind "Utility"
	files
	{
		"%{wks.location}/data/apis/**.json"
	}

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/apis -o:tmp/%{cfg.platform}/codegen -n:trader -t:hyperschema"
		}		
		rebuildcommands {
			"{RMDIR} tmp/%{cfg.platform}/codegen/**api.*",
			"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/apis -o:tmp/%{cfg.platform}/codegen -n:trader -t:hyperschema"
		}
		cleancommands {
			"{RMDIR} tmp/%{cfg.platform}/codegen/**api.*",
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
