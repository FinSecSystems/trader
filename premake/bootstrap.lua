project "bootstrap"
    kind "Makefile"
	location "%{wks.location}/tmp/projects"
	targetdir "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}/"
	buildcommands {
		"{MKDIR} %{wks.location}/bin/%{cfg.platform}/debug-static",
		"{MKDIR} %{wks.location}/bin/%{cfg.platform}/debug-shared",
		"{MKDIR} %{wks.location}/bin/%{cfg.platform}/release-static",
		"{MKDIR} %{wks.location}/bin/%{cfg.platform}/release-shared"
	}

	filter { "system:windows" }
		toolset "v140"
		targetname "libeay64MD.dll"

	filter { "system:linux" }
		targetname "libssl.so"
		buildcommands {
			"{COPY} %{wks.location}/packages/%{pocoPackageLinux}.%{pocoPackageVersionLinux}-debug-shared/lib/*.* %{wks.location}/bin/%{cfg.platform}/debug-shared/",
			"{COPY} %{wks.location}/packages/%{pocoPackageLinux}.%{pocoPackageVersionLinux}-release-shared/lib/*.* %{wks.location}/bin/%{cfg.platform}/release-shared/"
		}

	filter { "action:vs2015", "system:windows" }
		buildcommands {
			"{COPY} %{wks.location}/%{pocoPathVS2015}/build/native/x64/*.dll %{wks.location}/bin/%{cfg.platform}/debug-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2015}/build/native/x64/*.dll %{wks.location}/bin/%{cfg.platform}/release-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2015}/build/native/x64/*.pdb %{wks.location}/bin/%{cfg.platform}/debug-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2015}/build/native/x64/*.pdb %{wks.location}/bin/%{cfg.platform}/release-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2015}/lib/native/lib64/*.pdb %{wks.location}/lib/%{cfg.platform}/debug-static/",
			"{COPY} %{wks.location}/%{pocoPathVS2015}/lib/native/lib64/*.pdb %{wks.location}/lib/%{cfg.platform}/release-static/"
		}

	filter { "action:vs2017", "system:windows" }
		buildcommands {
			"{COPY} %{wks.location}/%{pocoPathVS2017}/build/native/x64/*.dll %{wks.location}/bin/%{cfg.platform}/debug-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2017}/build/native/x64/*.dll %{wks.location}/bin/%{cfg.platform}/release-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2017}/build/native/x64/*.pdb %{wks.location}/bin/%{cfg.platform}/debug-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2017}/build/native/x64/*.pdb %{wks.location}/bin/%{cfg.platform}/release-shared/",
			"{COPY} %{wks.location}/%{pocoPathVS2017}/lib/native/lib64/*.pdb %{wks.location}/lib/%{cfg.platform}/debug-static/",
			"{COPY} %{wks.location}/%{pocoPathVS2017}/lib/native/lib64/*.pdb %{wks.location}/lib/%{cfg.platform}/release-static/"
		}

	filter { "system:windows" }
		buildcommands {
			"{COPY} %{wks.location}/%{gtestPathDynamic}/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/x64/Debug/*.dll %{wks.location}/bin/%{cfg.platform}/debug-shared",
			"{COPY} %{wks.location}/%{gtestPathDynamic}/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/x64/Release/*.dll %{wks.location}/bin/%{cfg.platform}/release-shared",
			"{COPY} %{wks.location}/%{gtestPathDynamic}/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/x64/Debug/*.pdb %{wks.location}/bin/%{cfg.platform}/debug-shared",
			"{COPY} %{wks.location}/%{gtestPathDynamic}/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/x64/Release/*.pdb %{wks.location}/bin/%{cfg.platform}/release-shared",
		}

	configuration "with-vld"
		buildcommands {
			"{COPY} %{wks.location}/%{visualLeakDetectorPath}lib/native/address-model-64/lib/*.* %{wks.location}/bin/%{cfg.platform}/debug-shared",
			"{COPY} %{wks.location}/%{visualLeakDetectorPath}lib/native/address-model-64/lib/*.* %{wks.location}/bin/%{cfg.platform}/debug-static",
			"{COPY} %{wks.location}/%{visualLeakDetectorPath}lib/native/address-model-64/lib/*.* %{wks.location}/bin/%{cfg.platform}/release-shared",
			"{COPY} %{wks.location}/%{visualLeakDetectorPath}lib/native/address-model-64/lib/*.* %{wks.location}/bin/%{cfg.platform}/release-static"
		}