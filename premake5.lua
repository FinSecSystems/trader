	workspace "trader"
        editorintegration "On"
		configurations { "release", "debug" }
        platforms { "Win64", "Win64-Clang", "Win64-MSClang" }
        objdir "tmp"

        filter { "platforms:Win64" }
            system "Windows"
            architecture "x64"
            toolset "v140"
		    flags { "ExtraWarnings", "MultiProcessorCompile" }
            buildoptions    { "/GR-", "/doc" }

        filter { "platforms:Win64-Clang" }
            system "Windows"
            architecture "x64"
            toolset "msc-llvm-vs2014"

        filter { "platforms:Win64-MSClang" }
            system "Windows"
            architecture "x64"
            toolset "v140_clang_c2"
            buildoptions    { "-frtti", "-fms-compatibility" }

		filter "configurations:debug"
			defines     "_DEBUG"
            links { "MSVCRTD.LIB" }
            linkoptions { "/NODEFAULTLIB:msvcrt" }

		filter "configurations:release"
			defines     "NDEBUG"
			optimize    "Full"
			flags       { "NoBufferSecurityCheck", "NoRuntimeChecks" }

		filter { "configurations:debug", "platforms:Win64" }
			symbols		"On"

		filter { "configurations:debug", "platforms:Win64-MSClang" }
			buildoptions    { "-g2", "-Wall" }

		filter "action:vs*"
			defines     { "_CRT_SECURE_NO_DEPRECATE", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }

		filter { "system:windows", "configurations:release" }
			flags       { "NoIncrementalLink", "LinkTimeOptimization" }

	project "trader"
		targetname  "trader"
		language    "C++"
		kind        "ConsoleApp"
		includedirs { "source", "deps/task_scheduler/include", "samples", "deps/IntelSEAPI/ittnotify/include" }
		debugdir    "samples/profile"
		pchheader   "stdafx.h"
		pchsource   "samples/profile/stdafx.cpp"
		links       "deps/IntelSEAPI/bin/ittnotify64.lib"

		files
		{
			"*.txt", "**.lua","**.md",
			"samples/profile/**.h", "samples/profile/**.cpp",
			"include/**.h",
			"samples/common/**.h", "samples/common/**.cpp",
			"deps/IntelSEAPI/ittnotify/include/*.h", "deps/IntelSEAPI/ittnotify/include/*.hpp", "deps/IntelSEAPI/ittnotify/include/*.cpp"
		}

		excludes
		{
		}

		filter "configurations:debug"
			targetdir   "bin/debug"
			debugdir    "samples/profile"

		filter "configurations:release"
			targetdir   "bin/release"
			debugdir    "samples/profile"

		filter "system:windows"

