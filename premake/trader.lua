project "trader"
	location	"%{wks.location}/tmp/projects"
	targetname	"trader"
	language	"C++"
	kind		"ConsoleApp"
	targetdir	"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	debugdir	"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	links {
		"dataconnector"
	}
	includedirs {
		"%{wks.location}/",
		"%{wks.location}/sdk/include",
		"%{wks.location}/samples/utils",
		"%{wks.location}/samples/trader",
		"%{wks.location}/tmp/%{cfg.platform}/codegen",
		"%{wks.location}/deps/tinyfsm/include"
	}
	pchheader	"stdafx.h"
	pchsource	"%{wks.location}/samples/trader/stdafx.cpp"
	files {
		"%{wks.location}/sdk/include/**.h",
		"%{wks.location}/samples/trader/**.h",
		"%{wks.location}/samples/trader/**.cpp",
		"%{wks.location}/samples/utils/**.h",
		"%{wks.location}/samples/utils/**.cpp",
		"%{wks.location}/include/**.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/interface*.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/interface*.cpp",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/generic*.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/generic*.cpp",
		"%{wks.location}/bin/**.json",
		"%{wks.location}/bin/**.properties"
	}

	filter "files:%{wks.location}/deps/**.*"
		flags { "ExcludeFromBuild" }

	filter { "configurations:*shared" }
		defines "IMPORT_DATACONNECTOR"

	filter { "platforms:Linux64*", "system:linux" }
		files {
			"%{wks.location}/deps/poco/openssl/include/**.h",
			"%{wks.location}/deps/poco/openssl/src/**.cpp",
			"%{wks.location}/deps/poco/NetSSL_OpenSSL/include/**.h",
			"%{wks.location}/deps/poco/NetSSL_OpenSSL/src/**.cpp"
		}

	filter { "system:windows", "platforms:Win64" }
		links {
			"ittnotify64.lib",
			"Iphlpapi.lib",
			"ws2_32.lib",
			"crypt32.lib"
		}
		files {
			"%{wks.location}/%{intelSEAPIPath}/include/*.h",
			"%{wks.location}/%{intelSEAPIPath}/include/*.hpp",
		}

	filter { "platforms:Win64", "system:windows", "configurations:debug-static" }
		links { 
			"PocoFoundationmtd.lib",
			"PocoNetmtd.lib",
			"PocoNetSSLWinmtd.lib",
			"PocoUtilmtd.lib",
			"PocoCryptomtd.lib",
			"ssleay64MTd.lib",
			"libeay64MTd.lib",
			"PocoJSONmtd.lib",
			"PocoDatamtd.lib",
			"PocoXMLmtd.lib"
		}

	filter { "platforms:Win64", "system:windows", "configurations:release-static" }
		links { 
			"PocoFoundationmt.lib",
			"PocoNetmt.lib",
			"PocoNetSSLWinmt.lib",
			"PocoUtilmt.lib",
			"PocoCryptomt.lib",
			"ssleay64MT.lib",
			"libeay64MT.lib",
			"PocoJSONmt.lib",
			"PocoDatamt.lib",
			"PocoDataSQLitemt.lib",
			"PocoXMLmt.lib"
		}

	filter { "platforms:Win64", "system:windows", "configurations:debug-shared" }
		links { 
			"PocoFoundationd.lib",
			"PocoNetd.lib",
			"PocoNetSSLWind.lib",
			"PocoUtild.lib",
			"PocoCryptod.lib",
			"ssleay64MTd.lib",
			"libeay64MTd.lib",
			"PocoJSONd.lib",
			"PocoDatad.lib",
			"PocoDataSQLited.lib",
			"PocoXMLd.lib"
		}

	filter { "platforms:Win64", "system:windows", "configurations:release-shared" }
		links { 
			"PocoFoundation.lib",
			"PocoNet.lib",
			"PocoNetSSLWin.lib",
			"PocoUtil.lib",
			"PocoCrypto.lib",
			"ssleay64MT.lib",
			"libeay64MT.lib",
			"PocoJSON.lib",
			"PocoData.lib",
			"PocoDataSQLite.lib",
			"PocoXML.lib"
		}

	filter { "platforms:Linux64*", "system:linux" }
		links { 
			"pthread",
			"ssl",
			"crypto"
		}

	filter { "platforms:Linux64*", "system:linux", "configurations:debug*" }
		links { 
			"PocoFoundationd",
			"PocoUtild",
			"PocoJSONd",
			"PocoXMLd",
			"PocoNetd",
			"PocoDatad",
			"PocoDataSQLited",
			"PocoNetSSLd",
			"PocoCryptod"
		}

	filter { "platforms:Linux64*", "system:linux", "configurations:release*" }
		links { 
			"PocoFoundation",
			"PocoUtil",
			"PocoJSON",
			"PocoXML",
			"PocoNet",
			"PocoData",
			"PocoDataSQLite",
			"PocoNetSSL",
			"PocoCrypto"
			}
