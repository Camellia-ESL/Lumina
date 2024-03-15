#include "sprite_component.h"

namespace lumina
{
	void sprite_component::bind_texture(asset& texture_asset)
	{
		texture = texture_asset.get_resource<lumina::texture>();
		texture_asset_id = texture_asset.get_asset_id();
	}

	void sprite_component::unbind_texture()
	{
		texture = nullptr;
		texture_asset_id.clear();
	}
}