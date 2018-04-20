project "codegen"
	location	"%{wks.location}/tmp/projects"
	targetname  "codegen"
	language    "C++"
	kind        "ConsoleApp"
	targetdir   "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	debugdir    "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	configmap {
		["debug-static"] = "debug",
		["debug-shared"] = "debug",
		["release-static"] = "release",
		["release-shared"] = "release",
	}
	includedirs {
		"%{wks.location}/src/codegen"
	}
	pchheader   "stdafx.h"
	pchsource   "%{wks.location}/src/codegen/stdafx.cpp"
	debugargs {
		"/f:$(SolutionDir)deps\\quickfix\\spec\\FIX50SP2.xml",
		"/o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen",
		"/n:trader",
		"/t:xmlspec"
    }

	files
	{
		"%{wks.location}/src/codegen/**.h",
		"%{wks.location}/src/codegen/**.cpp",
		"%{wks.location}/include/**.h"
	}

	filter {"system:windows"}
		files {
			"*.txt",
			"*.md"
		}
		links {
			"Iphlpapi.lib"
		}

    filter "files:deps/**.*"
        flags { "ExcludeFromBuild" }

	excludes
	{
	}

	filter { "platforms:Linux64*", "system:linux", "configurations:debug"  }
		links { 
            "PocoFoundationd",
            "PocoUtild",
            "PocoJSONd",
			"PocoXMLd"
        }
							
	filter { "platforms:Linux64*", "system:linux", "configurations:release"  }
		links { 
            "PocoFoundation",
            "PocoUtil",
            "PocoJSON",
			"PocoXML"
        }

    filter { "platforms:Win64", "system:windows", "configurations:debug" }		
		links { 
            "PocoFoundationd.lib",
            "PocoUtild.lib",
            "PocoJSONd.lib",
			"PocoXMLd.lib"
        }

    filter { "platforms:Win64", "system:windows", "configurations:release" }		
		links	{ 
			"PocoFoundation.lib",
			"PocoUtil.lib",
			"PocoJSON.lib",
			"PocoXML.lib"
		}

	filter { "configurations:debug" }
		postbuildcommands {
			"{MKDIR} %{wks.location}/bin/%{cfg.platform}/debug-static",
			"{MKDIR} %{wks.location}/bin/%{cfg.platform}/debug-shared",
			"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/debug-static",
			"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/debug-shared"
		}

    filter { "configurations:release" }		
		postbuildcommands {
			"{MKDIR} %{wks.location}/bin/%{cfg.platform}/release-static",
			"{MKDIR} %{wks.location}/bin/%{cfg.platform}/release-shared",
			"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/release-static",
			"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/release-shared"
		}
