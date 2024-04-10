project "lumina_scripting_core"
   kind "SharedLib" 
   language "C#"
   dotnetframework "net4.5"
   
   files { "**.cs" }
	
   targetdir ("../Binaries/" .. OutputDirCs .. "/lumina_editor")
   objdir ("build/obj")

   filter "configurations:Debug"
       optimize "Off"
       symbols "Default"

   filter "configurations:Release"
       optimize "On"
       symbols "Default"
