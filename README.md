# Lumina Engine

An attempt to make a simple usable game engine that actually produces playable games.

### Building on Windows
- Install Vistual Studio with c++ desktop development
- Make sure to install the relative graphics sdk needed to build the engine (d3d11, vulkan is not yet supported)
- Clone repository
- Open project_scripts and run Setup-Windows.bat
- Go back in the main folder, open the generated solution.
- Build and run.

### Engine architecture
The engine it's a simple library (.lib) that is used from the editor (the actual engine editor) and the runtime_app_player (the player that execute the exported game/application).
It has Graphics API and Window System (platform independent) abstraction layers and currently only support D3D11.
Generates the project using Premake5. It currently only support Windows.

![diagram-export-3-22-2024-5_57_22-PM](https://github.com/VanityEmptiness/Lumina/assets/85369525/4c74971f-3045-44d7-ab8d-9dbe9fa5100d)
