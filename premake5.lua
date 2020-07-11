
workspace "Prism"
    cppdialect "C++17"
    location "Prism"
    architecture "x64"
    configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Includes to the project, relative to the workspace location
include "./Prism/vendor/glfw/"
include "./Prism/vendor/glad/"
include "./Prism/vendor/imgui/"

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
        "ImGui",
        "opengl32.lib"
    }

    files {
        "%{wks.name}/%{prj.name}/src/**.h",
        "%{wks.name}/%{prj.name}/src/**.hpp",
        "%{wks.name}/%{prj.name}/src/**.cpp",
        "%{wks.name}/%{prj.name}/src/**.c",
        "%{wks.name}/vendor/stb_image/**.h",
        "%{wks.name}/vendor/stb_image/**.cpp",
    }

    sysincludedirs {
        "./Prism/Prism/src/",
        "./Prism/vendor/spdlog/include/",
        "./Prism/vendor/glfw/include/",
        "./Prism/vendor/glad/include/",
        "./Prism/vendor/imgui/",
        "./Prism/vendor/glm/glm/",
        "./Prism/vendor/stb_image/"
    }

    includedirs {
        "./Prism/Prism/src",
        "./Prism/vendor/spdlog/include/",
        "./Prism/vendor/glfw/include/",
        "./Prism/vendor/glad/include/",
        "./Prism/vendor/imgui/",
        "./Prism/vendor/glm/glm/",
        "./Prism/vendor/stb_image/"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
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
        "./Prism/Prism/src",
        "./Prism/vendor/glm/glm/",
        "./Prism/vendor/imgui/",
    }

    sysincludedirs {
        "./Prism/vendor/spdlog/include/",
        "./Prism/Prism/src/",
        "./Prism/vendor/glm/glm/",
        "./Prism/vendor/imgui/",
    }

    links {
        "Prism",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "PRISM_PLATFORM_WINDOWS",
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
