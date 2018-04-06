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

		filter { "platforms:Win64", "system:windows", "configurations:*static" }
			flags { 
				"StaticRuntime"
				}

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
	
	group ""

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
		configmap {
			["debug-static"] = "debug",
			["debug-shared"] = "debug",
			["release-static"] = "release",
			["release-shared"] = "release",
		}
		includedirs {
			"src/codegen",
			"deps/poco/Foundation/include",
			"deps/poco/Util/include",
			"deps/poco/JSON/include",
			"deps/poco/XML/include"
			}
		pchheader   "stdafx.h"
		pchsource   "src/codegen/stdafx.cpp"
		debugargs {
			"/f:$(SolutionDir)deps\\quickfix\\spec\\FIX50SP2.xml",
			"/o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen",
			"/n:trader",
			"/t:xmlspec"
        }

		files
		{
			"src/codegen/**.h", "src/codegen/**.cpp",
			"include/**.h",
		}

		filter {"system:windows"}
			files {
				"*.txt","*.md",
				"deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
				"deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
				"deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
				"deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
				"deps/poco/NetSSL_Win/include/**.h", "deps/poco/NetSSL_Win/src/**.cpp",
				"deps/poco/openssl/include/**.h", "deps/poco/openssl/src/**.cpp",
				"deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp",
				"deps/poco/XML/include/**.h", "deps/poco/XML/src/**.cpp"
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

		filter { "platforms:Linux64*", "system:linux", "configurations:debug"  }
		    links       { 
                "deps/poco/lib/Linux/x86_64/PocoFoundationd",
                "deps/poco/lib/Linux/x86_64/PocoUtild",
                "deps/poco/lib/Linux/x86_64/PocoJSONd",
				"deps/poco/lib/Linux/x86_64/PocoXMLd"
                }
							
		filter { "platforms:Linux64*", "system:linux", "configurations:release"  }
		    links       { 
                "deps/poco/lib/Linux/x86_64/PocoFoundation",
                "deps/poco/lib/Linux/x86_64/PocoUtil",
                "deps/poco/lib/Linux/x86_64/PocoJSON",
				"deps/poco/lib/Linux/x86_64/PocoXML"
                }

        filter { "platforms:Win64", "system:windows", "configurations:debug" }		
		    links       { 
                "deps/poco/lib64/PocoFoundationd.lib",
                "deps/poco/lib64/PocoUtild.lib",
                "deps/poco/lib64/PocoJSONd.lib",
				"deps/poco/lib64/PocoXMLd.lib"
            }

        filter { "platforms:Win64", "system:windows", "configurations:release" }		
			links	{ 
				"deps/poco/lib64/PocoFoundation.lib",
				"deps/poco/lib64/PocoUtil.lib",
				"deps/poco/lib64/PocoJSON.lib",
				"deps/poco/lib64/PocoXML.lib"
			}

		filter { "configurations:debug"  }
			postbuildcommands {
				"{MKDIR} %{wks.location}/bin/%{cfg.platform}/debug-static",
				"{MKDIR} %{wks.location}/bin/%{cfg.platform}/debug-shared",
				"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/debug-static",
				"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/debug-shared"
			}

        filter { "configurations:release" }		
			postbuildcommands {
				"{MKDIR} %{wks.location}/bin/%{cfg.platform}/release-static",
				"{MKDIR} %{wks.location}/bin/%{cfg.platform}/release-shared",
				"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/release-static",
				"{COPY} %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.targetname}%{cfg.linktarget.extension} %{wks.location}/bin/%{cfg.platform}/release-shared"
			}

	project "apis"
		targetname "fybapi.h"
		dependson { 
			"codegen"
		}
		targetdir "tmp/%{cfg.platform}/codegen"
		kind "Utility"

		files
		{
			"data/apis/**.json"
		}

		filter { "platforms:Linux64*", "system:linux" }
			prebuildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/apis -o:tmp/%{cfg.platform}/codegen -n:trader -t:hyperschema"
			}		
			rebuildcommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**api.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/apis -o:tmp/%{cfg.platform}/codegen -n:trader -t:hyperschema"
			}
			cleancommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**api.*",
			}		
		
		filter { "platforms:Win64", "system:windows" }
			prebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:hyperschema"
			}
			rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\apis /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:hyperschema"
			}
			cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
			}

	project "configs"
		targetname "fybconfig.h"
		dependson { 
			"codegen"
		}
		kind "Utility"
		targetdir "tmp/%{cfg.platform}/codegen"

		files
		{
			"data/configs/**.json"
		}

		filter { "platforms:Win64", "system:windows" }
			prebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:jsonschema"
			}
			rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\configs /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:jsonschema"
			}
		   cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		   }

		filter { "platforms:Linux64*", "system:linux" }
			prebuildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/configs -o:tmp/%{cfg.platform}/codegen -n:trader -t:jsonschema"
			}
			rebuildcommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**config.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/configs -o:tmp/%{cfg.platform}/codegen -n:trader -t:jsonschema"
			}
			cleancommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**config.*",
			}

	project "databases"
		dependson { 
			"codegen"
		}
		kind		"Utility"
		targetdir	"tmp/%{cfg.platform}/codegen"
		targetname	"fybdatabase.h"

		files
		{
            "data/databases/**.json"
		}

		filter { "platforms:Win64", "system:windows" }
		   prebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\databases /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:databaseschema"
		   }

		   rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /i:$(SolutionDir)data\\databases /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:databaseschema"
		   }

		   cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		   }

		filter { "platforms:Linux64*", "system:linux" }
			prebuildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/databases -o:tmp/%{cfg.platform}/codegen -n:trader -t:databaseschema"
			}
			rebuildcommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**database.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -i:data/databases -o:tmp/%{cfg.platform}/codegen -n:trader -t:databaseschema"
			}
			cleancommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**database.*",
			}

	project "interface"
		dependson { 
			"codegen"
		}
		kind		"Utility"
		targetname	"interface.h"
		targetdir	"tmp/%{cfg.platform}/codegen"

		files {
            "deps/quickfix/spec/FIX50SP2.xml"
		}

		filter { "platforms:Win64", "system:windows" }
		   prebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /f:$(SolutionDir)deps/quickfix/spec/FIX50SP2.xml /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:xmlspec"
		   }
		   rebuildcommands {
				"PATH=$(SolutionDir)deps\\poco\\bin64",
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen",
				"$(SolutionDir)bin\\%{cfg.platform}\\%{cfg.buildcfg}\\codegen.exe /f:$(SolutionDir)deps/quickfix/spec/FIX50SP2.xml /o:$(SolutionDir)tmp\\%{cfg.platform}\\codegen /n:trader /t:xmlspec"
		   }
		   cleancommands {
				"{RMDIR} $(SolutionDir)tmp\\%{cfg.platform}\\codegen"
		   }

		filter { "platforms:Linux64*", "system:linux" }
			prebuildcommands {
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -f:deps/quickfix/spec/FIX50SP2.xml -o:tmp/%{cfg.platform}/codegen -n:trader -t:xmlspec"
			}
			rebuildcommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**database.*",
				"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:deps/poco/lib/Linux/x86_64 bin/%{cfg.platform}/%{cfg.buildcfg}/codegen -f:deps/quickfix/spec/FIX50SP2.xml -o:tmp/%{cfg.platform}/codegen -n:trader -t:xmlspec"
			}
			cleancommands {
				"{RMDIR} tmp/%{cfg.platform}/codegen/**interface.*",
			}

	project "dataconnector"
		targetname	"dataconnector"
		language	"C++"
		targetdir	"bin/%{cfg.platform}/%{cfg.buildcfg}"
		debugdir	"bin/%{cfg.platform}/%{cfg.buildcfg}"
		dependson { 
			"apis",
			"configs",
			"databases",
			"interface"
		}
		includedirs {
			".",
			"sdk/include",
			"src",
			"src/dataconnector",
			"deps/poco/Net/include",
			"deps/poco/Crypto/include",
			"deps/poco/Foundation/include",
			"deps/poco/Util/include",
			"deps/poco/openssl/include",
			"deps/poco/JSON/include",
			"deps/poco/Data/include",
			"deps/poco/Data/SQLite/include",
			"tmp/%{cfg.platform}/codegen"
		}
		pchheader	"stdafx.h"
		pchsource	"src/dataconnector/stdafx.cpp"
		files {
			"sdk/include/**.h",
			"src/dataconnector/**.h", "src/dataconnector/**.cpp",
			"include/**.h",	
			"tmp/%{cfg.platform}/codegen/**.h", "tmp/%{cfg.platform}/codegen/**.cpp"
		}

		filter "files:deps/**.*"
			flags { "ExcludeFromBuild" }

		excludes {
		}

		filter { "configurations:*static" }
			kind		"StaticLib"
			targetdir	"lib/%{cfg.platform}/%{cfg.buildcfg}"

		filter { "configurations:*shared" }
			defines		"EXPORT_DATACONNECTOR"
			kind		"SharedLib"
			implibdir	"lib/%{cfg.platform}/%{cfg.buildcfg}"
			targetdir	"bin/%{cfg.platform}/%{cfg.buildcfg}"

		filter { "platforms:Linux64*", "system:linux" }
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
			}
			links {
				"Iphlpapi.lib",
				"ws2_32.lib",
				"crypt32.lib"
			}
			files {
				"deps/poco/Crypto/include/**.h", "deps/poco/Crypto/src/**.cpp",
				"deps/poco/Foundation/include/**.h", "deps/poco/Foundation/src/**.cpp",
				"deps/poco/JSON/include/**.h", "deps/poco/JSON/src/**.cpp",
				"deps/poco/Net/include/**.h", "deps/poco/Net/src/**.cpp",
				"deps/poco/Util/include/**.h", "deps/poco/Util/src/**.cpp",
				"deps/poco/Data/**.h", "deps/poco/Data/**.cpp",
				"deps/poco/NetSSL_Win/include/**.h", "deps/poco/NetSSL_Win/src/**.cpp"
			}

		filter { "platforms:Win64", "system:windows", "configurations:debug-static" }
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
			postbuildcommands {
				"{COPY} %{wks.location}/deps/poco/lib64/openssl64mtd.pdb %{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}",		
			}

		filter { "platforms:Win64", "system:windows", "configurations:debug-shared" }
			links { 
				"deps/poco/lib64/PocoFoundationd.lib",
				"deps/poco/lib64/PocoNetd.lib",
				"deps/poco/lib64/PocoNetSSLWind.lib",
				"deps/poco/lib64/PocoUtild.lib",
				"deps/poco/lib64/PocoCryptod.lib",
				"deps/poco/lib64/ssleay64MTd.lib",
				"deps/poco/lib64/libeay64MTd.lib",
				"deps/poco/lib64/PocoJSONd.lib",
				"deps/poco/lib64/PocoDatad.lib",
				"deps/poco/lib64/PocoDataSQLited.lib",
				"deps/poco/lib64/PocoXMLd.lib"
			}

		filter { "platforms:Win64", "system:windows", "configurations:release-static" }
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

		filter { "platforms:Win64", "system:windows", "configurations:release-shared" }
			links { 
				"deps/poco/lib64/PocoFoundation.lib",
				"deps/poco/lib64/PocoNet.lib",
				"deps/poco/lib64/PocoNetSSLWin.lib",
				"deps/poco/lib64/PocoUtil.lib",
				"deps/poco/lib64/PocoCrypto.lib",
				"deps/poco/lib64/ssleay64MT.lib",
				"deps/poco/lib64/libeay64MT.lib",
				"deps/poco/lib64/PocoJSON.lib",
				"deps/poco/lib64/PocoData.lib",
				"deps/poco/lib64/PocoDataSQLite.lib",
				"deps/poco/lib64/PocoXML.lib"
			}

		filter { "platforms:Linux64*", "system:linux" }
			links { 
				"pthread",
				"ssl",
				"crypto"
			}

		filter { "platforms:Linux64*", "system:linux", "configurations:debug*" }
			links { 
				"deps/poco/lib/Linux/x86_64/PocoFoundationd",
				"deps/poco/lib/Linux/x86_64/PocoUtild",
				"deps/poco/lib/Linux/x86_64/PocoJSONd",
				"deps/poco/lib/Linux/x86_64/PocoXMLd",
				"deps/poco/lib/Linux/x86_64/PocoNetd",
				"deps/poco/lib/Linux/x86_64/PocoDatad",
				"deps/poco/lib/Linux/x86_64/PocoDataSQLited",
				"deps/poco/lib/Linux/x86_64/PocoNetSSLd",
				"deps/poco/lib/Linux/x86_64/PocoCryptod"
			}

		filter { "platforms:Linux64*", "system:linux", "configurations:release*" }
			links { 
				"deps/poco/lib/Linux/x86_64/PocoFoundation",
				"deps/poco/lib/Linux/x86_64/PocoUtil",
				"deps/poco/lib/Linux/x86_64/PocoJSON",
				"deps/poco/lib/Linux/x86_64/PocoXML",
				"deps/poco/lib/Linux/x86_64/PocoNet",
				"deps/poco/lib/Linux/x86_64/PocoData",
				"deps/poco/lib/Linux/x86_64/PocoDataSQLite",
				"deps/poco/lib/Linux/x86_64/PocoNetSSL",
				"deps/poco/lib/Linux/x86_64/PocoCrypto"
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
			"databases",
			"interface"
		}
		links {
			"dataconnector"
		}
		includedirs {
			".",
			"sdk/include",
			"samples/utils",
			"samples/trader",
			"deps/poco/Net/include",
			"deps/poco/Crypto/include",
			"deps/poco/Foundation/include",
			"deps/poco/Util/include",
			"deps/poco/openssl/include",
			"deps/poco/JSON/include",
			"deps/poco/Data/include",
			"deps/poco/Data/SQLite/include",
			"tmp/%{cfg.platform}/codegen",
			"deps/tinyfsm/include"
		}
		pchheader	"stdafx.h"
		pchsource	"samples/trader/stdafx.cpp"
		files {
			"*.txt", "*.md",
			"sdk/include/**.h",
			"samples/trader/**.h", "samples/trader/**.cpp",
			"samples/utils/**.h", "samples/utils/**.cpp",
			"include/**.h",
			"tmp/%{cfg.platform}/codegen/interface*.h", "tmp/%{cfg.platform}/codegen/interface*.cpp",
			"tmp/%{cfg.platform}/codegen/generic*.h", "tmp/%{cfg.platform}/codegen/generic*.cpp",
			"bin/**.json", "bin/**.properties"
		}

		filter "files:deps/**.*"
			flags { "ExcludeFromBuild" }

		excludes {
		}

		filter { "configurations:*shared" }
			defines "IMPORT_DATACONNECTOR"

		filter { "platforms:Linux64*", "system:linux" }
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
				"deps/intel_se_api/ittnotify/include",
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
			}

		filter { "platforms:Win64", "system:windows", "configurations:debug-static" }
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

		filter { "platforms:Win64", "system:windows", "configurations:release-static" }
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

		filter { "platforms:Win64", "system:windows", "configurations:debug-shared" }
			links { 
				"deps/poco/lib64/PocoFoundationd.lib",
				"deps/poco/lib64/PocoNetd.lib",
				"deps/poco/lib64/PocoNetSSLWind.lib",
				"deps/poco/lib64/PocoUtild.lib",
				"deps/poco/lib64/PocoCryptod.lib",
				"deps/poco/lib64/ssleay64MTd.lib",
				"deps/poco/lib64/libeay64MTd.lib",
				"deps/poco/lib64/PocoJSONd.lib",
				"deps/poco/lib64/PocoDatad.lib",
				"deps/poco/lib64/PocoDataSQLited.lib",
				"deps/poco/lib64/PocoXMLd.lib"
			}

		filter { "platforms:Win64", "system:windows", "configurations:release-shared" }
			links { 
				"deps/poco/lib64/PocoFoundation.lib",
				"deps/poco/lib64/PocoNet.lib",
				"deps/poco/lib64/PocoNetSSLWin.lib",
				"deps/poco/lib64/PocoUtil.lib",
				"deps/poco/lib64/PocoCrypto.lib",
				"deps/poco/lib64/ssleay64MT.lib",
				"deps/poco/lib64/libeay64MT.lib",
				"deps/poco/lib64/PocoJSON.lib",
				"deps/poco/lib64/PocoData.lib",
				"deps/poco/lib64/PocoDataSQLite.lib",
				"deps/poco/lib64/PocoXML.lib"
			}

		filter { "platforms:Linux64*", "system:linux" }
			links { 
				"pthread",
				"ssl",
				"crypto"
			}

		filter { "platforms:Linux64*", "system:linux", "configurations:debug*" }
			links { 
				"deps/poco/lib/Linux/x86_64/PocoFoundationd",
				"deps/poco/lib/Linux/x86_64/PocoUtild",
				"deps/poco/lib/Linux/x86_64/PocoJSONd",
				"deps/poco/lib/Linux/x86_64/PocoXMLd",
				"deps/poco/lib/Linux/x86_64/PocoNetd",
				"deps/poco/lib/Linux/x86_64/PocoDatad",
				"deps/poco/lib/Linux/x86_64/PocoDataSQLited",
				"deps/poco/lib/Linux/x86_64/PocoNetSSLd",
				"deps/poco/lib/Linux/x86_64/PocoCryptod"
			}

		filter { "platforms:Linux64*", "system:linux", "configurations:release*" }
			links { 
				"deps/poco/lib/Linux/x86_64/PocoFoundation",
				"deps/poco/lib/Linux/x86_64/PocoUtil",
				"deps/poco/lib/Linux/x86_64/PocoJSON",
				"deps/poco/lib/Linux/x86_64/PocoXML",
				"deps/poco/lib/Linux/x86_64/PocoNet",
				"deps/poco/lib/Linux/x86_64/PocoData",
				"deps/poco/lib/Linux/x86_64/PocoDataSQLite",
				"deps/poco/lib/Linux/x86_64/PocoNetSSL",
				"deps/poco/lib/Linux/x86_64/PocoCrypto"
				}

		filter { "system:windows" }
			debugenvs {
				"PATH=$(SolutionDir)deps\\poco\\bin64"
			}
