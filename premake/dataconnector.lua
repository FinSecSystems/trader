project "dataconnector"
	targetname	"dataconnector"
	language	"C++"
	targetdir	"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	debugdir	"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
	dependson { 
		"apis",
		"configs",
		"databases",
		"interface"
	}
	includedirs {
		"%{wks.location}/",
		"%{wks.location}/sdk/include",
		"%{wks.location}/src",
		"%{wks.location}/src/dataconnector",
		"%{wks.location}/tmp/%{cfg.platform}/codegen"
	}
	pchheader	"stdafx.h"
	pchsource	"%{wks.location}/src/dataconnector/stdafx.cpp"
	files {
		"%{wks.location}/sdk/include/**.h",
		"%{wks.location}/src/dataconnector/**.h",
		"%{wks.location}/src/dataconnector/**.cpp",
		"%{wks.location}/include/**.h",	
		"%{wks.location}/tmp/%{cfg.platform}/codegen/**.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/**.cpp"
	}

	filter "files:%{wks.location}/deps/**.*"
		flags { "ExcludeFromBuild" }

	excludes {
	}

	filter { "configurations:*static" }
		kind		"StaticLib"
		targetdir	"%{wks.location}/lib/%{cfg.platform}/%{cfg.buildcfg}"

	filter { "configurations:*shared" }
		defines		"EXPORT_DATACONNECTOR"
		kind		"SharedLib"
		implibdir	"%{wks.location}/lib/%{cfg.platform}/%{cfg.buildcfg}"
		targetdir	"%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"

	filter { "platforms:Linux64*", "system:linux" }
		files {
			"%{wks.location}/deps/poco/openssl/include/**.h",
			"%{wks.location}/deps/poco/openssl/src/**.cpp",
			"%{wks.location}/deps/poco/NetSSL_OpenSSL/include/**.h",
			"%{wks.location}/deps/poco/NetSSL_OpenSSL/src/**.cpp"
		}

	filter { "system:windows", "platforms:Win64" }
		links {
			"Iphlpapi.lib",
			"ws2_32.lib",
			"crypt32.lib"
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
			"PocoDataSQLitemtd.lib",
			"PocoXMLmtd.lib"
		}

	filter { "platforms:Win64", "action:vs2015", "system:windows" }
		postbuildcommands {
			"{COPY} %{wks.location}/%{pocoPathVS2015}lib/native/lib64/openssl64mtd.pdb %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}",		
		}

	filter { "platforms:Win64", "action:vs2017", "system:windows" }
		postbuildcommands {
			"{COPY} %{wks.location}/%{pocoPathVS2017}lib/native/lib64/openssl64mtd.pdb %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}",		
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
