#pragma once

#include "component.h"
#include "graphics/texture.h"
#include "assets_system/asset.h"

#include "glm/glm.hpp"

namespace lumina
{
	struct sprite_component : public component
	{
		enum class shapes
		{
			QUAD
		}shape{ shapes::QUAD };

		// Note that this will not be used if there already is a texture
		glm::vec4 color{ 1.0f, 1.0f, 0.0f, 1.0f };
		
		// Bind a texture
		void bind_texture(asset& texture_asset);

		// Unbind the binded texture
		void unbind_texture();

		// Wheter if there is a texture binded or not
		const bool has_texture() const { return texture_ != nullptr; }

		// Get's the binded texture or nullptr if there isn't one
		texture* get_texture() { return texture_; }

		// Get's the texture asset id if there is a texture binded
		const std::string& get_texture_asset_id() const { return texture_asset_id_; }

	private:

		// Should not be directly modified, instead use bind_texture
		texture* texture_ = nullptr;

		// Should not be directly modified, instead use bind_texture
		std::string texture_asset_id_ = "";

	};
}