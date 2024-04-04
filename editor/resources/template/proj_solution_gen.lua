workspace "LuminaScript"
   configurations { "Debug", "Release", "Dist" }

project "LuminaScript"
   kind "SharedLib" 
   language "C#"
   dotnetframework "net4.5"
   
   files { "**.cs" }

   links
   {
      "lumina_scripting_core.dll",
   }

   targetdir ("compiled")
   objdir ("obj")

   filter "configurations:Debug"
       optimize "Off"
       symbols "Default"

   filter "configurations:Release"
       optimize "On"
       symbols "Default"

   filter "configurations:Dist"
       optimize "Full"
       symbols "Off"