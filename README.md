# Lumina Engine

An attempt to make a simple usable game engine that actually produces playable games.

### Building on Windows
- Install Vistual Studio with c++ desktop development and .net development 
- Make sure to install the relative graphics sdk needed to build the engine (d3d11, vulkan is not yet supported)
- Clone repository
- Open project_scripts and run Setup-Windows.bat
- Go back in the main folder, open the generated solution.
- Build.
- Once built make sure to copy the resources folder and mono_res, from the lumina_editor folder to Binaries/(%platform)/(%buildconfig)/lumina_editor (this is a one time step)
- Build the engine script core
- Build lumina again and run.

### Engine architecture
The engine it's a simple library (.lib) that is used from the editor (the actual engine editor) and the runtime_app_player (the player that execute the exported game/application).
It has Graphics API and Window System (platform independent) abstraction layers and currently only support D3D11.
Generates the project using Premake5. It currently only support Windows.

![diagram-export-4-12-2024-2_31_09-PM](https://github.com/VanityEmptiness/Lumina/assets/85369525/dbe0841e-3681-40f4-bb6a-9b93a800b1de)
