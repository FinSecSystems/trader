pocoPackageVS2015 = "finsec.poco-windows-v140"
pocoPackageVS2017 = "finsec.poco-windows-v141"
pocoPackageVersion = "1.8.0.1"
gTestPackage = "gtest-vc140-static-64"
gTestPackageVersion = "1.1.0"

pocoPathVS2015	= "packages/%{pocoPackageVS2015}.%{pocoPackageVersion}/"
pocoPathVS2017	= "packages/%{pocoPackageVS2017}.%{pocoPackageVersion}/"
gtestPath		= "packages/%{gTestPackage}.%{gTestPackageVersion}/"
	
workspace "trader"
	editorintegration "On"
	configurations {
			"debug-static",
			"debug-shared",
			"release-static",
			"release-shared"
		}
    platforms {
			"Win64",
			"Win64-Clang",
			"Win64-MSClang",
			"Linux64-gcc",
			"Linux64-Clang"
		}
	objdir "tmp"

	filter { "system:linux" }
		removeplatforms {                
			"Win64",
			"Win64-Clang",
			"Win64-MSClang"
			}
		buildoptions    {
			"-std=c++11",
			"-shared-libgcc"
		}

	filter { "system:windows" }
		removeplatforms {                
			"Linux64-Clang",
			"Linux64-gcc"
			}

	filter { "platforms:Linux64*", "system:linux" }
		buildoptions {
			"-frtti",
			"-fexceptions",
			"-g"
		}
		linkoptions {
			"-g"
		}

	filter { "platforms:Linux64-gcc", "system:linux" }
		toolset "gcc"
		buildoptions {
			"-fpermissive",
			"-Wl,--no-as-needed"
		}
		linkoptions {
			"-Wl,--no-as-needed"
		}

	filter { "platforms:Linux64-clang", "system:linux" }
		toolset "clang"

	filter { "platforms:Win64", "system:windows" }
		system "Windows"
		architecture "x64"
		flags { 
			"MultiProcessorCompile"
			}
		buildoptions {
			-- "/GR-"  //Keep rtti enabled because Poco uses dynamic cast
			}
		warnings "Extra"
		disablewarnings { "4251" }
		includedirs {
			"%{gtestPath}lib/native/include"
		}

	filter { "platforms:Win64", "system:windows", "configurations:*static" }
		flags { 
			"StaticRuntime"
			}

	filter { "platforms:Win64", "action:vs2015", "system:windows" }
		toolset "v140"
		libdirs {
			"%{pocoPathVS2015}lib/native/lib64"
		}	
		debugenvs {
			"PATH=$(SolutionDir)%{pocoPathVS2015:gsub('/', '\\')}build\\native\\x64"
		}
		includedirs {
			"%{pocoPathVS2015}lib/native/include",
		}
		prebuildcommands {
			"PATH=$(SolutionDir)%{pocoPathVS2015:gsub('/', '\\')}build\\native\\x64"
		}
		rebuildcommands {
			"PATH=$(SolutionDir)%{pocoPathVS2015:gsub('/', '\\')}build\\native\\x64"
		}

	filter { "platforms:Win64", "action:vs2017", "system:windows" }
		toolset "v141"
		libdirs {
			"%{pocoPathVS2017}lib/native/lib64"
		}
		debugenvs {
			"PATH=$(SolutionDir)%{pocoPathVS2017:gsub('/', '\\')}build\\native\\x64"
		}
		includedirs {
			"%{pocoPathVS2017}lib/native/include",
		}
		prebuildcommands {
			"PATH=$(SolutionDir)%{pocoPathVS2017:gsub('/', '\\')}build\\native\\x64"
		}
		rebuildcommands {
			"PATH=$(SolutionDir)%{pocoPathVS2017:gsub('/', '\\')}build\\native\\x64"
		}

	filter { "platforms:Win64", "system:windows", "configurations:debug*" }
		libdirs { 
			"%{gtestPath}lib/native/libs/x64/static/Debug/"
		}

	filter { "platforms:Win64", "system:windows", "configurations:release*" }
		libdirs { 
			"%{gtestPath}lib/native/libs/x64/static/Release/"
		}

	filter { "system:linux" }
		includedirs {
			"deps/poco/Foundation/include",
			"deps/poco/Util/include",
			"deps/poco/JSON/include",
			"deps/poco/XML/include",
			"deps/poco/Net/include",
			"deps/poco/Crypto/include",
			"deps/poco/Foundation/include",
			"deps/poco/Util/include",
			"deps/poco/openssl/include",
			"deps/poco/JSON/include",
			"deps/poco/Data/include",
			"deps/poco/Data/SQLite/include",
			"deps/poco/NetSSL_OpenSSL/include"
		}
		libdirs {
			"deps/poco/lib/Linux/x86_64"
		}

	filter { "platforms:Win64-Clang", "system:windows" }
		system "Windows"
		architecture "x64"
		toolset "msc-llvm-vs2014"

	filter { "platforms:Win64-MSClang", "system:windows" }
		system "Windows"
		architecture "x64"
		toolset "v140_clang_c2"
		buildoptions {
			"-frtti",
			"-fms-compatibility"
		}

	filter "configurations:debug*"
		defines     "_DEBUG"
		symbols 	"On"

	filter "configurations:release*"
		defines     "NDEBUG"
		optimize    "Full"

	-- filter { "configurations:debug", "platforms:Win64" }
	-- 	links { 
	-- 		"MSVCRTD.LIB"
	-- 	}
	-- 	linkoptions {
	-- 		"/NODEFAULTLIB:msvcrt"
	-- 	}

	filter { "configurations:debug*", "platforms:Linux64-clang" }
		buildoptions {
			"-Wall"
		}

	filter { "configurations:debug*", "platforms:Win64-MSClang" }
		buildoptions {
			"-g2",
			"-Wall"
		}				

	filter { "configurations:release*", "platforms:Win64" }
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

	filter { "system:windows", "configurations:release*" }
		flags       {
            "NoIncrementalLink",
            "LinkTimeOptimization"
        }

	filter { "platforms:Linux64*", "system:linux" }
		buildoptions {
			"-Wno-unknown-pragmas",
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

	filter { "configurations:*static" }
		defines "USE_SHARED_LIBS"

	filter { "configurations:*shared" }
		defines "USE_DYNAMIC_LIBS"

group "Tools"
	project "codegen"
	project "genproj"

group "Generators"
	project "apis"
	project "configs"
	project "databases"
	project "interface"

group "Modules"
	project "dataconnector"

group "Samples"
	project "trader"

group "Apps"

group "Tests"
	project "bittrex_api_test"
	project "sample_app_test"
	project "connection_interface_test"
	
group ""

include "premake/genproj.lua"	
include "premake/codegen.lua"
include "premake/interface.lua"
include "premake/apis.lua"
include "premake/databases.lua"
include "premake/configs.lua"
include "premake/dataconnector.lua"
include "premake/trader.lua"
include "premake/bittrex_api_test.lua"
include "premake/sample_app_test.lua"
include "premake/connection_interface_test.lua"