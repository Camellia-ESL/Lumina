project "lumina_engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "vendors/**.h", "vendors/**.cpp" }

   includedirs
   {
      "src",
      "vendors"
   }

   libdirs
   {
      "../vendors_bin",
   }

   links
   {
      "d3d11.lib",
      "glfw3.lib"
   }

   characterset ("MBCS")

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "LUMINA_WIN32_PLATFORM" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       links { "yaml-cppd.lib", "d3dx11.lib" }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       links { "yaml-cpp.lib", "d3dx11.lib" }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       links { "yaml-cpp.lib", "d3dx11.lib" }