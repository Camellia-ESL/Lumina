#pragma once

#include "../scene_system/components/camera_component.h"
#include "graphics/texture.h"

namespace lumina
{
	// Abstracted 2d renderer can draw (quads)
	// every draw function and render pass function 
	// must be called beetwen an on_render function
	class renderer_2d_s
	{
	public:

		// Must be called before any draw
		static void begin_render_pass(camera_component* camera);

		// Must be called after drawing everything (draw everything on screen)
		static void end_render_pass();

		// Draw a colored quad
		static void draw_quad(const glm::mat4& model_transform, const glm::vec4& color);

		// Draw a textured quad
		static void draw_quad(const glm::mat4& model_transform, const texture& texture);

	private:

	};
}