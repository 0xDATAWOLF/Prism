
workspace "Prism"
    cppdialect "C++17"
    location "Prism"
    architecture "x64"
    configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Includes to the project, relative to the workspace location
include "./Prism/glfw/"
include "./Prism/vendor/glad/"

project "Prism"
    location ("%{wks.name}/Prism")
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    links {
        "GLFW",
        "glad",
        "opengl32.lib"
    }

    files {
        "%{wks.name}/%{prj.name}/src/**.h",
        "%{wks.name}/%{prj.name}/src/**.hpp",
        "%{wks.name}/%{prj.name}/src/**.cpp",
        "%{wks.name}/%{prj.name}/src/**.c"
    }

    sysincludedirs {
        "./Prism/vendor/spdlog/include/",
        "./Prism/glfw/include/",
        "./Prism/vendor/glad/include/",
        "./Prism/Prism/src/"
    }

    includedirs {
        "./Prism/vendor/spdlog/include/",
        "./Prism/glfw/include/",
        "./Prism/vendor/glad/include/",
        "./Prism/Prism/src"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
            "PRISM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../../bin/" .. outputdir .. "/Sandbox")
        }

    filter "system:macosx"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_OSX",
            "PRISM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        buildoptions "/MDd"
        defines "PRISM_DEBUG"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        buildoptions "/MD"
        defines "PRISM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        buildoptions "/MD"
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
        "./Prism/vendor/spdlog/include",
        "./Prism/Prism/src"
    }

    sysincludedirs {
        "./Prism/vendor/spdlog/include/",
        "./Prism/Prism/src/"
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
        buildoptions "/MDd"
        defines "PRISM_DEBUG"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        buildoptions "/MD"
        defines "PRISM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        buildoptions "/MD"
        defines "PRISM_DIST"
        optimize "On"
