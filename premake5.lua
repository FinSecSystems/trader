	workspace "trader"
        editorintegration "On"
		configurations {
                "release",
                "debug"
            }
        platforms {
                "Win64",
                "Win64-Clang",
                "Win64-MSClang"
            }
        objdir "tmp"

        filter { "platforms:Win64" }
            system "Windows"
            architecture "x64"
            toolset "v141"
		    flags { 
                "MultiProcessorCompile"
                }
            buildoptions    {
                "/GR-"
                }
			warnings "Extra"

        filter { "platforms:Win64-Clang" }
            system "Windows"
            architecture "x64"
            toolset "msc-llvm-vs2014"

        filter { "platforms:Win64-MSClang" }
            system "Windows"
            architecture "x64"
            toolset "v140_clang_c2"
            buildoptions    {
                "-frtti",
                "-fms-compatibility"
                }

		filter "configurations:debug"
			defines     "_DEBUG"
            links { "MSVCRTD.LIB" }
            linkoptions {
                "/NODEFAULTLIB:msvcrt"
                }

		filter "configurations:release"
			defines     "NDEBUG"
			optimize    "Full"
			flags       {
                "NoBufferSecurityCheck",
                "NoRuntimeChecks"
                }

		filter { "configurations:debug", "platforms:Win64" }
			symbols		"On"

		filter { "configurations:debug", "platforms:Win64-MSClang" }
			buildoptions    {
                "-g2",
                "-Wall"
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
		includedirs {
            "src/codegen",
            "deps/TaskScheduler/include",
            "deps/intel_se_api/ittnotify/include",
            "deps/poco/Net/include",
            "deps/poco/NetSSL_Win/include",
            "deps/poco/Crypto/include",
            "deps/poco/Foundation/include",
            "deps/poco/Util/include",
            "deps/poco/openssl/include",
            "deps/poco/JSON/include"
            }
		pchheader   "stdafx.h"
		pchsource   "src/codegen/stdafx.cpp"
		links       "deps/intel_se_api/bin/ittnotify64.lib"
        debugenvs {
            "PATH=$(SolutionDir)deps\\poco\\bin64"
        }
        debugargs {
            "/i:$(SolutionDir)data\\apis",
            "/o:$(SolutionDir)tmp\\codegen",
			"/n:trader",
			"/t:hyperschema"
        }

		files
		{
			"*.txt","**.md",
			"src/codegen/**.h", "src/codegen/**.cpp",
			"include/**.h",
			"deps/intel_se_api/ittnotify/include/*.h", "deps/intel_se_api/ittnotify/include/*.hpp", "deps/intel_se_api/ittnotify/include/*.cpp",
			"deps/TaskScheduler/include/**.h",
            "deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
            "deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
            "deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
            "deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
            "deps/poco/NetSSL_Win/include/**.h", "deps/poco/NetSSL_Win/src/**.cpp",
            "deps/poco/openssl/include/**.h", "deps/poco/openssl/src/**.cpp",
            "deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp"
		}

        filter "files:deps/**.*"
            flags { "ExcludeFromBuild" }

		excludes
		{
		}

		filter "configurations:debug"
			targetdir   "bin/debug"
			debugdir    "bin/debug"
		    links       { 
                "deps/poco/lib64/PocoFoundationd.lib",
                "deps/poco/lib64/PocoNetd.lib",
                "deps/poco/lib64/PocoNetSSLWind.lib",
                "deps/poco/lib64/PocoUtild.lib",
                "deps/poco/lib64/PocoCryptod.lib",
                "deps/poco/lib64/ssleay64MDd.lib",
                "deps/poco/lib64/libeay64MDd.lib",
                "deps/poco/lib64/PocoJSONd.lib"
                }

		filter "configurations:release"
			targetdir   "bin/release"
			debugdir    "bin/release"
		    links       { 
                "deps/poco/lib64/PocoFoundation.lib",
                "deps/poco/lib64/PocoNet.lib",
                "deps/poco/lib64/PocoNetSSLWin.lib",
                "deps/poco/lib64/PocoUtil.lib",
                "deps/poco/lib64/PocoCrypto.lib",
                "deps/poco/lib64/ssleay64MD.lib",
                "deps/poco/lib64/libeay64MD.lib",
                "deps/poco/lib64/PocoJSON.lib"
                }

	project "apis"
		targetname  "apis"
        dependson   { 
            "codegen"
            }
        kind "Makefile"

		files
		{
            "data/apis/**.json"
		}

       buildcommands {
			"PATH=$(SolutionDir)deps\\poco\\bin64",
            "$(SolutionDir)bin\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\codegen /n:trader /t:hyperschema"
       }

       rebuildcommands {
			"PATH=$(SolutionDir)deps\\poco\\bin64",
            "{RMDIR} $(SolutionDir)tmp\codegen",
            "$(SolutionDir)bin\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\codegen /n:trader /t:hyperschema"
       }

       cleancommands {
            "{RMDIR} $(SolutionDir)tmp\\codegen"
       }

	project "config"
		targetname  "config"
        dependson   { 
            "codegen"
            }
        kind "Makefile"

		files
		{
            "data/configs/**.json"
		}

       buildcommands {
			"PATH=$(SolutionDir)deps\\poco\\bin64",
            "$(SolutionDir)bin\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\codegen /n:trader /t:jsonschema"
       }

       rebuildcommands {
			"PATH=$(SolutionDir)deps\\poco\\bin64",
            "{RMDIR} $(SolutionDir)tmp\codegen",
            "$(SolutionDir)bin\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\codegen /n:trader /t:jsonschema"
       }

       cleancommands {
            "{RMDIR} $(SolutionDir)tmp\\codegen"
       }

	project "trader"
		targetname  "trader"
		language    "C++"
		kind        "ConsoleApp"
        dependson   { 
            "apis"
            }
		includedirs {
            "src",
            "deps/TaskScheduler/include",
            "deps/intel_se_api/ittnotify/include",
            "deps/poco/Net/include",
            "deps/poco/NetSSL_Win/include",
            "deps/poco/Crypto/include",
            "deps/poco/Foundation/include",
            "deps/poco/Util/include",
            "deps/poco/openssl/include",
            "deps/poco/JSON/include",
			"tmp/codegen"
            }
		pchheader   "stdafx.h"
		pchsource   "src/trader/stdafx.cpp"
		links       "deps/intel_se_api/bin/ittnotify64.lib"
        debugenvs {
            "PATH=$(SolutionDir)deps\\poco\\bin64"
        }

		files
		{
			"*.txt", "**.md",
			"src/trader/**.h", "src/trader/**.cpp",
			"include/**.h",
			"deps/intel_se_api/ittnotify/include/*.h", "deps/intel_se_api/ittnotify/include/*.hpp", "deps/intel_se_api/ittnotify/include/*.cpp",
			"deps/TaskScheduler/include/**.h",
            "deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
            "deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
            "deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
            "deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
            "deps/poco/NetSSL_Win/include/**.h", "deps/poco/NetSSL_Win/src/**.cpp",
            "deps/poco/openssl/include/**.h", "deps/poco/openssl/src/**.cpp",
            "deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp",
            "tmp/codegen/**.h", "tmp/codegen/**.cpp",
			"bin/**..json"
		}

        filter "files:deps/**.*"
            flags { "ExcludeFromBuild" }

		excludes
		{
		}

		filter "configurations:debug"
			targetdir   "bin/debug"
			debugdir    "bin/debug"
		    links       { 
                "deps/poco/lib64/PocoFoundationd.lib",
                "deps/poco/lib64/PocoNetd.lib",
                "deps/poco/lib64/PocoNetSSLWind.lib",
                "deps/poco/lib64/PocoUtild.lib",
                "deps/poco/lib64/PocoCryptod.lib",
                "deps/poco/lib64/ssleay64MDd.lib",
                "deps/poco/lib64/libeay64MDd.lib",
                "deps/poco/lib64/PocoJSONd.lib"
                }

		filter "configurations:release"
			targetdir   "bin/release"
			debugdir    "bin/release"
		    links       { 
                "deps/poco/lib64/PocoFoundation.lib",
                "deps/poco/lib64/PocoNet.lib",
                "deps/poco/lib64/PocoNetSSLWin.lib",
                "deps/poco/lib64/PocoUtil.lib",
                "deps/poco/lib64/PocoCrypto.lib",
                "deps/poco/lib64/ssleay64MD.lib",
                "deps/poco/lib64/libeay64MD.lib",
                "deps/poco/lib64/PocoJSON.lib"
                }

		filter "system:windows"



