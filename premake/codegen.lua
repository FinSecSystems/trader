project "codegen"
	location	"%{wks.location}/tmp/projects"
	targetname  "codegen"
	language    "C++"
	kind        "ConsoleApp"
	targetdir   "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	debugdir    "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	includedirs {
		"%{wks.location}/src/codegen"
	}
	pchheader   "stdafx.h"
	pchsource   "%{wks.location}/src/codegen/stdafx.cpp"
	files
	{
		"%{wks.location}/src/codegen/**.h",
		"%{wks.location}/src/codegen/**.cpp",
		"%{wks.location}/include/**.h"
	}
	dependson
	{
		"bootstrap"
	}

	filter {"system:windows"}
		files {
			"*.txt",
			"*.md"
		}
		links {
			"Iphlpapi.lib"
		}
		debugargs {
			"/f:$(SolutionDir)deps\\quickfix\\spec\\FIX50SP2.xml",
			"/o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen",
			"/n:trader",
			"/t:xmlspec"
		}

    filter "files:deps/**.*"
        flags { "ExcludeFromBuild" }

	filter { "platforms:Linux64*", "system:linux" }
		links { 
			"pthread",
			"z"
		}

	filter { "system:linux", "configurations:debug*"  }
		links { 
			"PocoEncodingsd",
			"PocoUtild",
			"PocoJSONd",
			"PocoXMLd",
			"PocoFoundationd"
        }
							
	filter { "system:linux", "configurations:release*"  }
		links { 
			"PocoEncodings",
			"PocoUtil",
			"PocoJSON",
			"PocoXML",
			"PocoFoundation"
        }

	filter { "platforms:Win64", "system:windows", "configurations:debug-static" }
		links { 
			"PocoFoundationmtd.lib",
			"PocoUtilmtd.lib",
			"PocoJSONmtd.lib",
			"PocoXMLmtd.lib"
		}

	filter { "platforms:Win64", "system:windows", "configurations:release-static" }
		links { 
			"PocoFoundationmt.lib",
			"PocoUtilmt.lib",
			"PocoJSONmt.lib",
			"PocoXMLmt.lib"
		}

	filter { "platforms:Win64", "system:windows", "configurations:debug-shared" }
		links { 
			"PocoFoundationd.lib",
			"PocoUtild.lib",
			"PocoJSONd.lib",
			"PocoXMLd.lib"
		}

	filter { "platforms:Win64", "system:windows", "configurations:release-shared" }
		links { 
			"PocoFoundation.lib",
			"PocoUtil.lib",
			"PocoJSON.lib",
			"PocoXML.lib"
		}