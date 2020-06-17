
workspace "Prism"
    cppdialect "C++14"
    location "Prism"
    architecture "x64"
    configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Includes to the project, relative to the workspace location
include "./Prism/glfw/"

project "Prism"
    location ("%{wks.name}/Prism")
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    links {
        "GLFW"
    }

    files {
        "%{wks.name}/%{prj.name}/src/**.h",
        "%{wks.name}/%{prj.name}/src/**.hpp",
        "%{wks.name}/%{prj.name}/src/**.cpp",
        "%{wks.name}/%{prj.name}/src/**.c"
    }

    sysincludedirs {
        "./Prism/vendor/spdlog/include/",
        "./Prism/glfw/include/"
    }

    includedirs {
        "./Prism/vendor/spdlog/include/",
        "./Prism/glfw/include/"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
            "PRISM_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../../bin/" .. outputdir .. "/Sandbox")
        }

    filter "system:macosx"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_OSX",
            "PRISM_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "PRISM_DEBUG"
        symbols "On"
        optimize "Off"

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
    cppdialect "C++14"
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
        "./Prism/vendor/spdlog/include",
        "./%{wks.name}/Prism/src"
    }

    sysincludedirs {
        "./Prism/vendor/spdlog/include/",
    }

    links {
        "Prism"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
        }

    filter "system:macosx"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_OSX",
        }

    filter "system:windows"
        systemversion "latest"

    filter "system:macosx"
        systemversion "latest"

    filter "configurations:Debug"
        defines "PRISM_DEBUG"
        symbols "On"
        optimize "Off"

    filter "configurations:Debug"
        defines "PRISM_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "PRISM_DIST"
        optimize "On"
