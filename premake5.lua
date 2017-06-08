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

	project "trader"
		targetname  "trader"
		language    "C++"
		kind        "ConsoleApp"
		includedirs {
            "src",
            "deps/task_scheduler/include",
            "deps/intel_se_api/ittnotify/include",
            "deps/poco/Net/include",
            "deps/poco/NetSSL_OpenSSL/include",
            "deps/poco/Crypto/include",
            "deps/poco/Foundation/include",
            "deps/poco/Util/include",
            "deps/poco/openssl/include",
            "deps/poco/JSON/include"
            }
		debugdir    "src"
		pchheader   "stdafx.h"
		pchsource   "src/stdafx.cpp"
		links       "deps/intel_se_api/bin/ittnotify64.lib"
        debugenvs {
            "PATH=$(SolutionDir)deps\\poco\\bin64"
        }

		files
		{
			"*.txt", "**.lua","**.md",
			"src/**.h", "src/**.cpp",
			"include/**.h",
			"src/**.h", "src/**.cpp",
			"deps/intel_se_api/ittnotify/include/*.h", "deps/intel_se_api/ittnotify/include/*.hpp", "deps/intel_se_api/ittnotify/include/*.cpp",
            "deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
            "deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
            "deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
            "deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
            "deps/poco/NetSSL_OpenSSL/include/**.h", "deps/poco/NetSSL_OpenSSL/src/**.cpp",
            "deps/poco/openssl/include/**.h", "deps/poco/openssl/src/**.cpp",
            "deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp",
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
                "deps/poco/lib64/PocoNetSSLd.lib",
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
                "deps/poco/lib64/PocoNetSSL.lib",
                "deps/poco/lib64/PocoUtil.lib",
                "deps/poco/lib64/PocoCrypto.lib",
                "deps/poco/lib64/ssleay64MD.lib",
                "deps/poco/lib64/libeay64MD.lib",
                "deps/poco/lib64/PocoJSON.lib"
                }

		filter "system:windows"

        filter "files:premake5.lua"
           -- A message to display while this build step is running (optional)
           buildmessage 'Generating Projects'

           -- One or more commands to run (required)
           buildcommands {
              '$(SolutionDir)build\\genproj.cmd'
           }

           -- One or more outputs resulting from the build (required)
           buildoutputs { '$(SolutionDir)trader.sln' }

