	workspace "trader"
        editorintegration "On"
		configurations {
                "release",
                "debug"
            }
        platforms {
                "Win64",
                "Win64-Clang",
                "Win64-MSClang",
				"Linux64-Clang",
				"Linux64-gcc",
            }
        objdir "tmp"

		filter { "system:linux" }
			removeplatforms {                
				"Win64",
                "Win64-Clang",
                "Win64-MSClang"
				}
			buildoptions    {
                "-std=c++11"
            }

		filter { "system:windows" }
			removeplatforms {                
				"Linux64-Clang",
				"Linux64-gcc"
				}

		filter { "platforms:Linux64-gcc", "system:linux" }
			toolset "gcc"

		filter { "platforms:Linux64-clang", "system:linux" }
			toolset "clang"

        filter { "platforms:Win64", "system:windows" }
            system "Windows"
            architecture "x64"
		    flags { 
                "MultiProcessorCompile",
				"StaticRuntime"
                }
            buildoptions    {
                "/GR-"
                }
			warnings "Extra"

		filter { "platforms:Win64", "action:vs2015", "system:windows" }
            toolset "v140"

		filter { "platforms:Win64", "action:vs2017", "system:windows" }
            toolset "v141"

        filter { "platforms:Win64-Clang", "system:windows" }
            system "Windows"
            architecture "x64"
            toolset "msc-llvm-vs2014"

        filter { "platforms:Win64-MSClang", "system:windows" }
            system "Windows"
            architecture "x64"
            toolset "v140_clang_c2"
            buildoptions    {
                "-frtti",
                "-fms-compatibility"
                }

		filter "configurations:debug"
			defines     "_DEBUG"

		filter "configurations:release"
			defines     "NDEBUG"
			optimize    "Full"

		filter { "configurations:debug", "platforms:Win64" }
			symbols		"On"
            links { "MSVCRTD.LIB" }
            linkoptions {
                "/NODEFAULTLIB:msvcrt"
                }

		filter { "configurations:debug", "platforms:Win64-MSClang" }
			buildoptions    {
                "-g2",
                "-Wall"
                }

		filter { "configurations:release", "platforms:Win64" }
			flags       {
                "NoBufferSecurityCheck",
                "NoRuntimeChecks"
                }

		filter "action:vs*"
			defines     { 
                "_CRT_SECURE_NO_DEPRECATE",
                "_CRT_SECURE_NO_WARNINGS",
                "_CRT_NONSTDC_NO_WARNINGS"
                }

		filter { "system:windows", "configurations:release" }
			flags       {
                "NoIncrementalLink",
                "LinkTimeOptimization"
            }

        filter "files:premake5.lua"
           -- A message to display while this build step is running (optional)
           buildmessage 'Generating Projects'

           -- One or more commands to run (required)
           buildcommands {
              '$(SolutionDir)build\\genproj.cmd'
           }

           -- One or more outputs resulting from the build (required)
           buildoutputs { '$(SolutionDir)trader.sln' }

    project "genproj"
		targetname  "genproj"
        kind "Makefile"

		files
		{
            "*.lua"
		}

		filter { "system:linux" }
			buildcommands {
				"%{wks.location}/tools/bin/premake/premake5 gmake"
			}

			rebuildcommands {
				"{RMDIR} %{wks.location}/Makefile",
				"{RMDIR} %{wks.location}/*.make",
				"%{wks.location}/tools/bin/premake/premake5 gmake"
			}

			cleancommands {
				"{RMDIR} %{wks.location}Makefile",
				"{RMDIR} %{wks.location}*.make"
			}

		filter { "system:windows" }
			buildcommands {
				"$(SolutionDir)build\\genproj.cmd"
			}

			rebuildcommands {
				"{RMDIR} $(SolutionDir)*.vcxproj*",
				"{RMDIR} $(SolutionDir)*.sln*",
				"$(SolutionDir)build\\genproj.cmd"
			}

			cleancommands {
				"{RMDIR} $(SolutionDir)*.vcxproj*",
				"{RMDIR} $(SolutionDir)*.sln*",
			}
		
		
	project "codegen"
		targetname  "codegen"
		language    "C++"
		kind        "ConsoleApp"
		targetdir   "bin/%{cfg.platform}/%{cfg.buildcfg}"
		debugdir    "bin/%{cfg.platform}/%{cfg.buildcfg}"
		includedirs {
            "src/codegen",
            "deps/poco/Foundation/include",
            "deps/poco/Util/include",
            "deps/poco/JSON/include"
            }
		pchheader   "stdafx.h"
		pchsource   "src/codegen/stdafx.cpp"
        debugargs {
            "/i:$(SolutionDir)data\\apis",
            "/o:$(SolutionDir)tmp\\codegen",
			"/n:trader",
			"/t:hyperschema"
        }

		files
		{
			"src/codegen/**.h", "src/codegen/**.cpp",
			"include/**.h",
            "deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
            "deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
            "deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
            "deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
            "deps/poco/NetSSL_Win/include/**.h", "deps/poco/NetSSL_Win/src/**.cpp",
            "deps/poco/openssl/include/**.h", "deps/poco/openssl/src/**.cpp",
            "deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp"
		}

		filter {"system:windows"}
			includedirs {
				"deps/TaskScheduler/include",
				"deps/intel_se_api/ittnotify/include"
				}
			files {
				"*.txt","**.md",
				"deps/intel_se_api/ittnotify/include/*.h", "deps/intel_se_api/ittnotify/include/*.hpp", "deps/intel_se_api/ittnotify/include/*.cpp",
				"deps/TaskScheduler/include/**.h",
			}
			links       {
				"Iphlpapi.lib"
			}
			debugenvs {
				"PATH=$(SolutionDir)deps\\poco\\bin64"
			}

        filter "files:deps/**.*"
            flags { "ExcludeFromBuild" }

		excludes
		{
		}

		filter { "platforms:Linux64-clang", "system:linux", "configurations:debug"  }
		    links       { 
                "deps/poco/lib/Linux/x86_64/PocoFoundationd",
                "deps/poco/lib/Linux/x86_64/PocoUtild",
                "deps/poco/lib/Linux/x86_64/PocoJSONd",
				"deps/poco/lib/Linux/x86_64/PocoXMLd"
                }
				
		filter { "platforms:Linux64-clang", "system:linux", "configurations:release"  }
		    links       { 
                "deps/poco/lib/Linux/x86_64/PocoFoundation",
                "deps/poco/lib/Linux/x86_64/PocoUtil",
                "deps/poco/lib/Linux/x86_64/PocoJSON",
				"deps/poco/lib/Linux/x86_64/PocoXML"
                }

        filter { "platforms:Win64", "system:windows", "configurations:debug" }		
		    links       { 
                "deps/poco/lib64/PocoFoundationmtd.lib",
                "deps/poco/lib64/PocoUtilmtd.lib",
                "deps/poco/lib64/PocoJSONmtd.lib",
				"deps/poco/lib64/PocoXMLmtd.lib"
                }

        filter { "platforms:Win64", "system:windows", "configurations:release" }		
			links	{ 
				"deps/poco/lib64/PocoFoundationmt.lib",
				"deps/poco/lib64/PocoUtilmt.lib",
				"deps/poco/lib64/PocoJSONmt.lib",
				"deps/poco/lib64/PocoXMLmt.lib"
				}

	project "apis"
		targetname  "fybapi.h"
		dependson   { 
			"codegen"
			}
		targetdir	"tmp/codegen"
		kind "Makefile"

		files
		{
			"data/apis/**.json"
		}

		filter { "platforms:Linux64-clang", "system:linux" }
			kind "Utility"
			buildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/apis -o:tmp/codegen -n:trader -t:hyperschema"
			}		
			rebuildcommands {
				"{RMDIR} tmp/codegen/**api.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/apis -o:tmp/codegen -n:trader -t:hyperschema"
			}
			cleancommands {
				"{RMDIR} tmp/codegen/**api.*",
			}		
		
		filter { "platforms:Win64", "system:windows" }
			buildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\codegen /n:trader /t:hyperschema"
			}
			rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\codegen /n:trader /t:hyperschema"
			}
			cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\codegen"
			}

	project "configs"
		targetname  "fybconfig.h"
		dependson	{ 
			"codegen"
		}
		kind "Makefile"
		targetdir	"tmp/codegen"

		files
		{
			"data/configs/**.json"
		}

		filter { "platforms:Win64", "system:windows" }
			buildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\codegen /n:trader /t:jsonschema"
			}

			rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\codegen /n:trader /t:jsonschema"
			}

		   cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\codegen"
		   }

		filter { "platforms:Linux64-clang", "system:linux" }
			kind "Utility"
			buildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/configs -o:tmp/codegen -n:trader -t:jsonschema"
			}
			rebuildcommands {
				"{RMDIR} tmp/codegen/**api.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/configs -o:tmp/codegen -n:trader -t:jsonschema"
			}
			cleancommands {
				"{RMDIR} tmp/codegen/**api.*",
			}

	project "databases"
		targetname  "fybdatabase.h"
		dependson { 
			"codegen"
		}
		kind "Makefile"
		targetdir	"tmp/codegen"

		files
		{
            "data/databases/**.json"
		}

		filter { "platforms:Win64", "system:windows" }
		   buildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\databases /o:$(SolutionDir)tmp\\codegen /n:trader /t:databaseschema"
		   }

		   rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\databases /o:$(SolutionDir)tmp\\codegen /n:trader /t:databaseschema"
		   }

		   cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\codegen"
		   }

		filter { "platforms:Linux64-clang", "system:linux" }
			kind "Utility"
			buildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/databases -o:tmp/codegen -n:trader -t:databaseschema"
			}
			rebuildcommands {
				"{RMDIR} tmp/codegen/**api.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/databases -o:tmp/codegen -n:trader -t:databaseschema"
			}
			cleancommands {
				"{RMDIR} tmp/codegen/**api.*",
			}

	project "trader"
		targetname	"trader"
		language	"C++"
		kind		"ConsoleApp"
		targetdir	"bin/%{cfg.platform}/%{cfg.buildcfg}"
		debugdir	"bin/%{cfg.platform}/%{cfg.buildcfg}"
		dependson { 
			"apis",
			"configs",
			"databases"
		}
		includedirs {
			".",
			"src",
			"src/trader",
			"deps/poco/Net/include",
			"deps/poco/Crypto/include",
			"deps/poco/Foundation/include",
			"deps/poco/Util/include",
			"deps/poco/openssl/include",
			"deps/poco/JSON/include",
			"deps/poco/Data/include",
			"deps/poco/Data/SQLite/include",
			"tmp/codegen"
		}
		pchheader	"stdafx.h"
		pchsource	"src/trader/stdafx.cpp"
		files
		{
			"*.txt", "*.md",
			"src/trader/**.h", "src/trader/**.cpp",
			"include/**.h",
			"deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
			"deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
			"deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
			"deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
			"deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp",
			"deps/poco/Data/**.h", "deps/poco/Data/**.cpp",
			"tmp/codegen/**.h", "tmp/codegen/**.cpp",
			"bin/**.json", "bin/**.properties"
		}

		filter "files:deps/**.*"
			flags { "ExcludeFromBuild" }

		excludes
		{
		}

		filter { "system:linux", "platforms:Linux64-clang" }
			includedirs {
				"deps/poco/NetSSL_OpenSSL/include",
			}
			files {
				"deps/poco/openssl/include/**.h", "deps/poco/openssl/src/**.cpp",
				"deps/poco/NetSSL_OpenSSL/include/**.h", "deps/poco/NetSSL_OpenSSL/src/**.cpp"
			}

		filter { "system:windows", "platforms:Win64" }
			includedirs {
				"deps/poco/NetSSL_Win/include",
				"deps/TaskScheduler/include",
				"deps/intel_se_api/ittnotify/include",
				"deps/cef/cef_binary_3.3163.1667.g88c82d2_windows64/include"
				}
			links {
				"deps/intel_se_api/bin/ittnotify64.lib",
				"Iphlpapi.lib",
				"ws2_32.lib",
				"crypt32.lib"
			}
			files {
				"deps/intel_se_api/ittnotify/include/*.h",
				"deps/intel_se_api/ittnotify/include/*.hpp",
				"deps/intel_se_api/ittnotify/include/*.cpp",
				"deps/TaskScheduler/include/**.h",
				"deps/poco/NetSSL_Win/include/**.h", "deps/poco/NetSSL_Win/src/**.cpp"
			}

		filter { "platforms:Win64", "system:windows", "configurations:debug" }
			links { 
				"deps/poco/lib64/PocoFoundationmtd.lib",
				"deps/poco/lib64/PocoNetmtd.lib",
				"deps/poco/lib64/PocoNetSSLWinmtd.lib",
				"deps/poco/lib64/PocoUtilmtd.lib",
				"deps/poco/lib64/PocoCryptomtd.lib",
				"deps/poco/lib64/ssleay64MTd.lib",
				"deps/poco/lib64/libeay64MTd.lib",
				"deps/poco/lib64/PocoJSONmtd.lib",
				"deps/poco/lib64/PocoDatamtd.lib",
				"deps/poco/lib64/PocoDataSQLitemtd.lib",
				"deps/poco/lib64/PocoXMLmtd.lib"
			}

		filter { "platforms:Win64", "system:windows", "configurations:release" }
			links { 
				"deps/poco/lib64/PocoFoundationmt.lib",
				"deps/poco/lib64/PocoNetmt.lib",
				"deps/poco/lib64/PocoNetSSLWinmt.lib",
				"deps/poco/lib64/PocoUtilmt.lib",
				"deps/poco/lib64/PocoCryptomt.lib",
				"deps/poco/lib64/ssleay64MT.lib",
				"deps/poco/lib64/libeay64MT.lib",
				"deps/poco/lib64/PocoJSONmt.lib",
				"deps/poco/lib64/PocoDatamt.lib",
				"deps/poco/lib64/PocoDataSQLitemt.lib",
				"deps/poco/lib64/PocoXMLmt.lib"
				}
			filter { "platforms:Linux64-clang", "system:linux" }
			links { 
				"pthread",
				"ssl",
				"crypto"
			}

		filter { "platforms:Linux64-clang", "system:linux", "configurations:debug" }
			links { 
				"deps/poco/lib/Linux/x86_64/PocoFoundationd",
				"deps/poco/lib/Linux/x86_64/PocoUtild",
				"deps/poco/lib/Linux/x86_64/PocoJSONd",
				"deps/poco/lib/Linux/x86_64/PocoXMLd",
				"deps/poco/lib/Linux/x86_64/PocoNetd",
				"deps/poco/lib/Linux/x86_64/PocoDatad",
				"deps/poco/lib/Linux/x86_64/PocoDataSQLited",
				"deps/poco/lib/Linux/x86_64/PocoXMLd",
				"deps/poco/lib/Linux/x86_64/PocoNetSSLd",
				"deps/poco/lib/Linux/x86_64/PocoCryptod"
			}

		filter { "platforms:Linux64-clang", "system:linux", "configurations:release" }
			links { 
				"deps/poco/lib/Linux/x86_64/PocoFoundation",
				"deps/poco/lib/Linux/x86_64/PocoUtil",
				"deps/poco/lib/Linux/x86_64/PocoJSON",
				"deps/poco/lib/Linux/x86_64/PocoXML",
				"deps/poco/lib/Linux/x86_64/PocoNet",
				"deps/poco/lib/Linux/x86_64/PocoData",
				"deps/poco/lib/Linux/x86_64/PocoDataSQLite",
				"deps/poco/lib/Linux/x86_64/PocoXML",
				"deps/poco/lib/Linux/x86_64/PocoNetSSL",
				"deps/poco/lib/Linux/x86_64/PocoCrypto"
				}

		filter { "configurations:release", "system:windows", "platforms:Win64" }
			debugenvs {
				"PATH=$(SolutionDir)deps\\poco\\bin64;$(SolutionDir)\\deps\\cef\\cef_binary_3.3163.1667.g88c82d2_windows64\\Release"
			}
			links {
				"deps\\cef\\cef_binary_3.3163.1667.g88c82d2_windows64\\Release\\libcef.lib",
				"deps\\cef\\cef_binary_3.3163.1667.g88c82d2_windows64\\Release\\cef_sandbox.lib"
			}

		filter { "configurations:debug", "system:windows", "platforms:Win64" }
			debugenvs {
				"PATH=$(SolutionDir)deps\\poco\\bin64;$(SolutionDir)\\deps\\cef\\cef_binary_3.3163.1667.g88c82d2_windows64\\Debug"
			}
			links {
				"deps\\cef\\cef_binary_3.3163.1667.g88c82d2_windows64\\Debug\\libcef.lib",
				"deps\\cef\\cef_binary_3.3163.1667.g88c82d2_windows64\\Debug\\cef_sandbox.lib"
			}

