	workspace "trader"
        editorintegration "On"
		configurations { "release", "debug" }
        platforms { "Win64", "Win64-Clang", "Win64-MSClang" }
        objdir "tmp"

        filter { "platforms:Win64" }
            system "Windows"
            architecture "x64"
            toolset "v140"
		    flags { "MultiProcessorCompile" }
            buildoptions    { "/GR-", "/doc" }
			warnings "Extra"

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
		includedirs { "src", "deps/task_scheduler/include", "deps/intel_se_api/ittnotify/include" }
		debugdir    "src"
		pchheader   "stdafx.h"
		pchsource   "src/stdafx.cpp"
		links       "deps/intel_se_api/bin/ittnotify64.lib"

		files
		{
			"*.txt", "**.lua","**.md",
			"src/**.h", "src/**.cpp",
			"include/**.h",
			"src/**.h", "src/**.cpp",
			"deps/intel_se_api/ittnotify/include/*.h", "deps/intel_se_api/ittnotify/include/*.hpp", "deps/intel_se_api/ittnotify/include/*.cpp"
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

