# Lumina Engine

An attempt to make a simple usable game engine that actually produces playable games.

### Building on Windows
- Clone repository
- Open project_scripts and run Setup-Windows.bat
- Go back in the main folder, open the generated solutions.
- Build and run.

### Engine architecture
The engine it's a simple library (.lib) that is used from the editor (the actual engine editor) and the runtime_app_player (the player that execute the exported game/application).
It has Graphics API and Window System (platform independent) abstraction layers and currently only support D3D11.
Generates the project using Premake5. It currently only support Windows.
