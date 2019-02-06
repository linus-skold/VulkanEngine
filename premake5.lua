--beware of the scope issue https://github.com/premake/premake-core/wiki/Scopes-and-Inheritance
workspace "Engine" --this is the solution name in a vs project if no filename specified
    --filename "whiteroom"
    configurations { "Debug" , "Release" }
    platforms { "Windows" }
    architecture "x64"
    includedirs { ".\\" }
    libdirs { "" }
    flags { "FatalCompileWarnings" }
    warnings "Extra"
    location "build"

    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"

    filter "kind:StaticLib"
        targetdir "%{wks.location}/lib/%{cfg.buildcfg}"

    filter "kind:WindowedApp"
        targetdir "%{wks.location}/bin/%{cfg.buildcfg}"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    
    project "Executable" --project name
        
        kind "WindowedApp" --type [ConsoleApp, WindowedApp, SharedLib, StaticLib, Makefile, Utility, None, AndroidProj], WindowedApp is important on Windows and Mac OS X
        language "C++" --language
        location ("./executable")
        
        dependson { "Core", "Graphics" }
        links { "Graphics", "Core" } --libraries to link
        
        files { "executable/*.cpp" }

        filter "platforms:Windows"
            defines { "_WIN32" }

    project "Graphics"
        kind "StaticLib"
        language "C++"
        location ("./graphics")    
        files { "graphics/*.cpp", "graphics/*.h" }

    project "Core"
        kind "StaticLib"
        language "C++"
        location ("./core")

        files { "core/**.cpp", "core/**.h" }
