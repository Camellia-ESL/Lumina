#include "renderer_2d.h"

#include "application/app.h"
#include "d3d11_2d_renderers/d3d11_quad_renderer.h"
#include "d3d11_2d_renderers/d3d11_lines_renderer.h"

#include "scene_system/components/transform_component.h"

namespace lumina
{
	void renderer_2d_s::begin_render_pass(camera_component* camera)
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_quad_renderer_s::begin_render_pass(camera);
			d3d11_lines_renderer_s::begin_render_pass(camera);
		}
	}

	void renderer_2d_s::end_render_pass()
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_lines_renderer_s::end_render_pass();
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

	void renderer_2d_s::draw_quad(const glm::mat4& model_transform, const texture& texture)
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_quad_renderer_s::draw_quad(model_transform, *((d3d11_texture*)texture.get_native_resource()));
		}
	}

	void renderer_2d_s::draw_line(const glm::mat4& model_transform, const glm::vec4& color)
	{
		graphics_api_e running_graphics_api = application_player::get_singleton().get_surface().get_graphics_driver().get_graphics_api_running();

		if (running_graphics_api == graphics_api_e::D3D11_API)
		{
			d3d11_lines_renderer_s::draw_line(model_transform, color);
		}
	}

	void renderer_2d_s::draw_grid(const glm::mat4& model_transform, const glm::vec4& color, float grid_size)
	{
		//@enhancement-[renderer_2d]: To optimize grid rendering we should also get the camera used for rendering and calculate worldPos
		// to check if the camera can see a line or not and eventually avoid rendering it
		constexpr const float y_axis_rot_angle = 90.0f;

		// Lambda to handle linear plans grid rendering computations
		const auto compute_linear_plan_rendering =
			[&](const transform_component& computation_transform, float lines_distance_signed) -> void
			{
				for (size_t i = 0; i < (grid_size / 2); i++)
				{
					transform_component temp_transform_per_line = computation_transform;
					temp_transform_per_line.translate({ 0.0f , 0.0f , lines_distance_signed * i });
					lumina::renderer_2d_s::draw_line(temp_transform_per_line.get_model_matrix(), color);
				}
			};

		const auto compute_grid_axis_render =
			[&](const transform_component& computation_transform) -> void
			{
				// Compute's the first positive half of the linear plan
				compute_linear_plan_rendering(computation_transform, 1.0f);

				// Compute's the second negative half of the linear plan
				compute_linear_plan_rendering(computation_transform, -1.0f);
			};

		// Create's a temporary model transform
		transform_component temp_model_transform{ model_transform };

		// Prepare the transform scaling it, to avoid multiple scales
		temp_model_transform.set_scale({ grid_size , 1.0f, 1.0f });

		// Compute's the horizontal x-axis plan
		compute_grid_axis_render(temp_model_transform);

		// Reset the scale
		temp_model_transform.set_scale({ 1.0f, 1.0f, 1.0f });

		// Prepare the rotation and the scale, to avoid multiple rotations/scalings
		temp_model_transform.rotate({ 0.0f, 1.0f, 0.0f }, glm::radians(y_axis_rot_angle));
		temp_model_transform.scale({ grid_size , 1.0f, 1.0f });

		// Compute's the horizontal y-axis plan
		compute_grid_axis_render(temp_model_transform);
	}
}