#include "sprite_component.h"

namespace lumina
{
	void sprite_component::bind_texture(asset& texture_asset)
	{
		texture_ = texture_asset.get_resource<lumina::texture>();
		texture_asset_id_ = texture_asset.get_asset_id();
	}

	void sprite_component::unbind_texture()
	{
		texture_ = nullptr;
		texture_asset_id_.clear();
	}
}