workspace "liLib"
	architecture "x64"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	defines { "UNICODE" }
	includedirs { "%{wks.location}", "%{wks.location}/include" }
	targetdir ("%{wks.location}/Build")
	objdir ("%{wks.location}/Intermediates/%{prj.name}_%{cfg.buildcfg}_%{cfg.system}/")
	filter "system:windows"
		staticruntime "off"
		systemversion "latest"
        	defines { "WIN32" }
	filter "configurations:Debug"
		symbols "on"
		defines {  "_DEBUG", }
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"
		symbols "on"

project "liLib"
	kind "StaticLib"
	files { "src/**.cpp", "include/**.h" }

project "Sandbox"
	kind "ConsoleApp"
	files { "sandbox/**.*" }
	links { "liLib" }