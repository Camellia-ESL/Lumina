#pragma once

#include "../../scene_system/components/camera_component.h"

#include "graphics/d3d11_api/d3d11_texture.h"

namespace lumina
{
	// Quad batch renderer 
	class d3d11_quad_renderer_s
	{
	public:

		// Begin a new render pass 
		static void begin_render_pass(camera_component* camera);
		
		// End the render pass and draws everything on screen
		static void end_render_pass();

		// Draw a colored quad (must be called after a render pass has started)
		static void draw_quad(const glm::mat4& quad_transform, const glm::vec4& color);

		// Draw a textured quad (must be called after a render pass has started)
		static void draw_quad(const glm::mat4& quad_transform, const d3d11_texture& texture);

		// Gets the number of max renderable quads
		static constexpr const uint32_t get_max_renderable_quads() { return MAX_RENDERABLE_QUADS_; }

		// Gets the number of max textures that can be submitted before automatically starting a new render pass
		static constexpr const uint32_t get_max_submittable_textures() { return MAX_TEXTURES_SLOT_; }

	private:

		static constexpr const uint32_t MAX_RENDERABLE_QUADS_ = 1000;
		static constexpr const uint32_t MAX_TEXTURES_SLOT_ = 8;

		// Should be called only once after the graphics got initialized
		// allocates all the resources needed from the renderer
		static void init();

		// Free all the allocated resources
		static void destroy();

	private:

		friend class d3d11_renderer;

	};
}