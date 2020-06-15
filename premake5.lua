
workspace "Prism"
    architecture "x64"
    configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 
project "Prism"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }

    include {
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
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }

    includedirs {
        "Prism/vendor/spdlog/include",
        "Prism/src",
        "Prism/vendor"
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