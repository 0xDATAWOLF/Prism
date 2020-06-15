
workspace "Prism"
    location "Prism"
    architecture "x64"
    configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 
project "Prism"
    location ("%{wks.name}/Prism")
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{wks.name}/%{prj.name}/src/**.h",
        "%{wks.name}/%{prj.name}/src/**.hpp",
        "%{wks.name}/%{prj.name}/src/**.cpp",
        "%{wks.name}/%{prj.name}/src/**.c"
    }

    includedirs {
        "%{wks.name}/vendor/spd/include"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
            "PRISM_BUILD_DLL"
        }

        postbuildcommands {
            ("copy %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "system:macosx"
        systemversion "latest"


        defines {
            "PRISM_PLATFORM_OSX",
            "PRISM_BUILD_DLL"
        }

        postbuildcommands {
            ("cp %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "PRISM_DEBUG"
        symbols "On"

    filter "configurations:Debug"
        defines "PRISM_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "PRISM_DIST"
        optimize "On"

project "Sandbox"
    location ("%{wks.name}/Sandbox")
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{wks.name}/%{prj.name}/src/**.h",
        "%{wks.name}/%{prj.name}/src/**.hpp",
        "%{wks.name}/%{prj.name}/src/**.cpp",
        "%{wks.name}/%{prj.name}/src/**.c"
    }

    includedirs {
        "${wks.name}/vendor/spdlog/include",
        "%{wks.name}/Prism/src",
        "${wks.name}/vendor"
    }

    links {
        "Prism"
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:macosx"
        systemversion "latest"

    filter "configurations:Debug"
        defines "PRISM_DEBUG"
        symbols "On"

    filter "configurations:Debug"
        defines "PRISM_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "PRISM_DIST"
        optimize "On"