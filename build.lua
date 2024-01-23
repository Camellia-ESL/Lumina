-- premake5.lua
workspace "lumina"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "lumina-editor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

-- Build files of Lumina containing every project
include "engine/build_engine.lua"
include "editor/build_editor.lua"