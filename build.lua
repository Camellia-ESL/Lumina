-- premake5.lua
workspace "lumina"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "lumina-editor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
EditorResourceDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}/lumina_editor/resources"

-- Build files of Lumina containing every project
include "engine/build_engine.lua"
include "editor/build_editor.lua"
include "runtime_player/build_runtime_player.lua"

workspace "lumina_scripting"
   configurations { "Debug", "Release" }

OutputDirCs = "%{cfg.system}-x86_64/%{cfg.buildcfg}"

include "scripting_core/build_scripting_core.lua"