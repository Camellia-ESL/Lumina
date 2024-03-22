#pragma once

#include "lumina.h"

#define LUMINA_EDITOR_GET_ASSET(asset_name, asset_type) editor_asset_manager::get_singleton().get_registry().get_asset_by_name(asset_name).get_resource<asset_type>()

namespace lumina_editor
{
	class LUMINA_SINGLETON_CLASS(editor_asset_manager)
	{
	public:

		// Contains the names of all the available textures loaded inside 
		// the editor asset manager (all the names are unique and match the exact name of the png file that contains the texture) 
		struct textures
		{
			static constexpr const char* folder = "img_folder";
			static constexpr const char* document = "img_document";
			static constexpr const char* refresh = "img_refresh";
			static constexpr const char* play_button = "img_play_button";
			static constexpr const char* stop_button = "img_stop_button";
		};

	public:

		editor_asset_manager() { on_load(); }

		// Get the asset registry
		lumina::assets_registry& get_registry() { return assets_registry_; }

	private:

		lumina::assets_registry assets_registry_;

		static constexpr const char* texture_default_file_format_ = ".png";

		void on_load();

	};
}