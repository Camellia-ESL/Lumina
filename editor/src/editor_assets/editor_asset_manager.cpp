#include "editor_asset_manager.h"

#include "../editor_compile_configs.h"

LUMINA_SINGLETON_DECL_INSTANCE(lumina_editor::editor_asset_manager);

#define LUMINA_EDITOR_ASSETS_DIR_PATH LUMINA_EDITOR_RESOURCES_PATH "assets/"

namespace lumina_editor
{
	static std::vector<std::string> textures_to_load =
	{
		editor_asset_manager::textures::folder,
		editor_asset_manager::textures::document,
		editor_asset_manager::textures::refresh
	};

	void editor_asset_manager::on_load()
	{
		for (const std::string& texture_name : textures_to_load)
		{
			// Load the textures and transfer ownership to the asset registry
			// @enhancement-[editor_asset_manager]: Add more checks to avoid crashes in case something went wrong.
			lumina::texture* texture = new lumina::texture{};
			std::string texture_file_path_complete = LUMINA_EDITOR_ASSETS_DIR_PATH + texture_name + texture_default_file_format_;
			bool result = texture->load_from_file(texture_file_path_complete);
			
			if (!result)
				throw std::runtime_error("Error loading vital editor texture asset: " + texture_name);
			
			lumina::asset& texture_asset = assets_registry_.create_asset<lumina::texture>(texture);
			texture_asset.set_name(texture_name);
		}
	}
}