project "bittrex_api_test"
	location "%{wks.location}/tmp/projects"
	configmap {
		["debug-static"] = "debug-static",
		["debug-shared"] = "debug-static",
		["release-static"] = "release-static",
		["release-shared"] = "release-static",
	}
	targetname	"bittrex_api_test"
	language	"C++"
	kind		"ConsoleApp"
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
		"%{wks.location}/src",
		"%{wks.location}/sdk/include",
		"%{wks.location}/samples/utils",
		"%{wks.location}/src/dataconnector",
		"%{wks.location}/tests/bittrex_api_test",
		"%{wks.location}/tmp/%{cfg.platform}/codegen",
		"%{wks.location}/deps/tinyfsm/include",
	}
	pchheader	"stdafx.h"
	pchsource	"%{wks.location}/tests/bittrex_api_test/stdafx.cpp"
	files {
		"%{wks.location}/sdk/include/**.h",
		"%{wks.location}/src/dataconnector/bittrex.h",
		"%{wks.location}/src/dataconnector/bittrex.cpp",
		"%{wks.location}/src/dataconnector/api*",
		"%{wks.location}/src/dataconnector/db*",
		"%{wks.location}/src/dataconnector/app*",
		"%{wks.location}/tests/bittrex_api_test/**.h",
		"%{wks.location}/tests/bittrex_api_test/**.cpp",
		"%{wks.location}/samples/utils/applicationhelper*",
		"%{wks.location}/include/**.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/interface*.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/interface*.cpp",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/generic*.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/generic*.cpp",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/bittrex*.h",
		"%{wks.location}/tmp/%{cfg.platform}/codegen/bittrex*.cpp",
		"%{wks.location}/bin/**.json",
		"%{wks.location}/bin/**.properties"
	}

	filter "files:%{wks.location}/deps/**.*"
		flags { "ExcludeFromBuild" }

	excludes {
	}

	filter { "platforms:Linux64*", "system:linux" }
		files {
			"%{wks.location}/deps/poco/openssl/include/**.h",
			"%{wks.location}/deps/poco/openssl/src/**.cpp",
			"%{wks.location}/deps/poco/NetSSL_OpenSSL/include/**.h",
			"%{wks.location}/deps/poco/NetSSL_OpenSSL/src/**.cpp"
		}

	filter { "system:windows", "platforms:Win64" }
		includedirs {
			"%{wks.location}/deps/intel_se_api/ittnotify/include",
			}
		links {
			"%{wks.location}/deps/intel_se_api/bin/ittnotify64.lib",
			"Iphlpapi.lib",
			"ws2_32.lib",
			"crypt32.lib",
			"gtest.lib"
		}
		files {
			"%{wks.location}/deps/intel_se_api/ittnotify/include/*.h",
			"%{wks.location}/deps/intel_se_api/ittnotify/include/*.hpp",
			"%{wks.location}/deps/intel_se_api/ittnotify/include/*.cpp",
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
			"PocoXMLmtd.lib",
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
			"PocoXMLmt.lib",
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
