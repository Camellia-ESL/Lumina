project "lumina_runtime_player"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",
      "../engine/src",
      "../engine/vendors"
   }

   libdirs
   {
      "../vendors_bin",
   }

   links
   {
      "lumina_engine",
      "glfw3.lib",
      "eglib.lib",
      "libgcmonosgen.lib",
      "libmini-sgen.lib",
      "libmonoruntime-sgen.lib",
      "libmono-static-sgen.lib",
      "libmonoutils.lib",
      "mono-2.0-sgen.lib",
      "MonoPosixHelper.lib"
   }

   targetdir ("../Binaries/" .. EditorResourceDir.. "/bin")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }
       links { "d3d11.lib", "d3dx11.lib", "Ws2_32.lib", "Version.lib", "Winmm.lib", "Bcrypt.lib", "D3DCompiler.lib" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       links { "yaml-cppd.lib" }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       links { "yaml-cpp.lib" }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       links { "yaml-cpp.lib" }