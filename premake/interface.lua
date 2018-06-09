project "interface"
	location	"%{wks.location}/tmp/projects"
	dependson { 
		"codegen"
	}
	kind		"Utility"
	targetname	"interface.h"
	targetdir	"%{wks.location}/tmp/%{cfg.platform}/codegen/"

	files {
        "%{wks.location}/deps/quickfix/spec/FIX50SP2.xml"
	}

	filter { "platforms:Linux64*", "system:linux" }
		prebuildcommands {
			"LD_LIBRARY_PATH=%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/:$$LD_LIBRARY_PATH %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -f:%{wks.location}/deps/quickfix/spec/FIX50SP2.xml -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:xmlspec"
		}
		rebuildcommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**database.*",
			"LD_LIBRARY_PATH=%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/:$$LD_LIBRARY_PATH %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -f:%{wks.location}/deps/quickfix/spec/FIX50SP2.xml -o:%{wks.location}/tmp/%{cfg.platform}/codegen -n:trader -t:xmlspec"
		}
		cleancommands {
			"{RMDIR} %{wks.location}/tmp/%{cfg.platform}/codegen/**interface.*",
		}

	filter { "platforms:Win64", "system:windows" }
		prebuildcommands {
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /f:$(SolutionDir)deps/quickfix/spec/FIX50SP2.xml /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:xmlspec"
		}
		rebuildcommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
			"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /f:$(SolutionDir)deps/quickfix/spec/FIX50SP2.xml /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:xmlspec"
		}
		cleancommands {
			"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		}
