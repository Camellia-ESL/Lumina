#include "renderer_2d.h"

#include "application/app.h"
#include "d3d11_2d_renderers/d3d11_quad_renderer.h"

namespace lumina
{
	void renderer_2d_s::begin_render_pass()
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_quad_renderer_s::begin_render_pass();
		}
	}

	void renderer_2d_s::end_render_pass()
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_quad_renderer_s::end_render_pass();
		}
	}

	void renderer_2d_s::draw_quad(const glm::mat4& model_transform, const glm::vec4& color)
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_quad_renderer_s::draw_quad(model_transform, color);
		}
	}
}