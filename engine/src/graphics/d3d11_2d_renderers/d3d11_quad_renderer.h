#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lumina
{
	// Quad batch renderer 
	class d3d11_quad_renderer_s
	{
	public:

		// Begin a new render pass 
		static void begin_render_pass();
		
		// End the render pass and draws everything on screen
		static void end_render_pass();

		// Draw a colored quad (must be called after a render pass has started)
		static void draw_quad(const glm::mat4& quad_transform, const glm::vec4& color);

		// Gets the number of max renderable quads
		static constexpr const uint32_t get_max_renderable_quads() { return max_renderable_quads_; }

	private:

		static constexpr const uint32_t max_renderable_quads_ = 1000;

		// Should be called only once after the graphics got initialized
		// allocates all the resources needed from the renderer
		static void init();

		// Free all the allocated resources
		static void destroy();

	private:

		friend class d3d11_renderer;

	};
}