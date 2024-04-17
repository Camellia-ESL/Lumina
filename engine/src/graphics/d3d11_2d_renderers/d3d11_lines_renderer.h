#pragma once

#include "../../scene_system/components/camera_component.h"

namespace lumina
{
	class d3d11_lines_renderer_s
	{
	public:

		// Begin a new render pass 
		static void begin_render_pass(camera_component* camera);

		// End the render pass and draws everything on screen
		static void end_render_pass();

		// Draw a colored line (must be called after a render pass has started)
		static void draw_line(const glm::mat4& quad_transform, const glm::vec4& color);

		// Gets the number of max renderable lines
		static constexpr const uint32_t get_max_renderable_lines() { return MAX_RENDERABLE_LINES_; }

	private:

		static constexpr const uint32_t MAX_RENDERABLE_LINES_ = 5000;

		// Should be called only once after the graphics got initialized
		// allocates all the resources needed from the renderer
		static void init();

		// Free all the allocated resources
		static void destroy();

	private:

		friend class d3d11_renderer;
	};
}