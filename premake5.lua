
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Prism"
    architecture "x64"
    configurations {"Debug","Release","Dist"}

project "Prism"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
    }

    include {
        "%{wks.name}/vendor/spd/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
            "PRISM_BUILD_DLL"
        }

        postbuildcommands {
            ("copy %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "system:macosx"
        cppdialect "C++17"
        staticruntime "On"
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

    