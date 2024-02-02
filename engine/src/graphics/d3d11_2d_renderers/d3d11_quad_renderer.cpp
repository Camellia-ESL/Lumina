#include "d3d11_quad_renderer.h"

#include "../d3d11_api/d3d11_api.h"

namespace lumina
{
	const std::string vertex_shader_src = R"(
		struct vertex_output
		{ 
			float4 position : SV_POSITION; 
			float4 color : COLOR; 
		};
	
		vertex_output v_main(float2 position : POSITION, float4x4 model : MODEL_TRANSFORM, float4 color : COLOR)
		{
			vertex_output output;
			output.position = mul(float4(position, 0.0f, 1.0f), model);
			output.color = color;

			return output;
		}
	)";

	const std::string pixel_shader_src = R"(
		float4 p_main(float4 position : SV_POSITION, float4 color : COLOR) : SV_Target
		{
			return color;
		}
	)";
		
	struct quad_vertex_t
	{
		glm::vec2 position;
		glm::mat4 model_transform;
		glm::vec4 color;
	};

	d3d11_vertex_buffer vertex_buffer{};
	d3d11_index_buffer index_buffer{};
	d3d11_vertex_shader vertex_shader{};
	d3d11_pixel_shader pixel_shader{};
	d3d11_input_layout_descriptor input_layout_descriptor{};
	d3d11_blend_state blend_state{};

	std::vector<quad_vertex_t> verticies{};
	uint32_t rendered_quads_this_frame = 0;
	const uint32_t verticies_per_quad = 4;
	const uint32_t indicies_per_quad = 6;
	
	void d3d11_quad_renderer_s::begin_render_pass()
	{
		// Clear the previous render pass
		verticies.clear();
		rendered_quads_this_frame = 0;
	}

	void d3d11_quad_renderer_s::end_render_pass()
	{
		if (rendered_quads_this_frame <= 0)
			return;

		// Enable all the d3d11 resources needed to render the quad
		vertex_buffer.enable();
		index_buffer.enable();
		vertex_shader.enable();
		pixel_shader.enable();
		input_layout_descriptor.enable();
		blend_state.enable();

		// Load the vertex buffer with the verticies of this render pass
		vertex_buffer.load_data(&verticies[0], sizeof(quad_vertex_t) * verticies.size());

		// Draw call, render all the quads
		d3d11_instance::get_singleton().get_device_context()->DrawIndexed(rendered_quads_this_frame * indicies_per_quad, 0, 0);
	}

	void d3d11_quad_renderer_s::draw_quad(const glm::mat4& quad_transform, const glm::vec4& color)
	{
		if (rendered_quads_this_frame >= max_renderable_quads_)
		{
			end_render_pass();
			begin_render_pass();
		}

		glm::mat4 transposed_transform = glm::transpose(quad_transform);

		verticies.push_back({ { -0.5f,  0.5f }, transposed_transform, color }); // Top left
		verticies.push_back({ { 0.5f,  0.5f }, transposed_transform, color }); // Top right
		verticies.push_back({ { 0.5f, -0.5f }, transposed_transform, color }); // Bottom right
		verticies.push_back({ { -0.5f, -0.5f }, transposed_transform, color }); // Bottom left

		rendered_quads_this_frame++;
	}

	void d3d11_quad_renderer_s::init()
	{
		// Allocate vertex buffer
		d3d11_vertex_buffer_alloc_info_t vertex_buffer_alloc_info{};
		vertex_buffer_alloc_info.buffer_size = d3d11_quad_renderer_s::get_max_renderable_quads() * (verticies_per_quad * sizeof(quad_vertex_t));
		vertex_buffer_alloc_info.data_stride = sizeof(quad_vertex_t);
		vertex_buffer_alloc_info.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		vertex_buffer.allocate(vertex_buffer_alloc_info);

		// Allocate index buffer
		std::vector<uint32_t> indicies;
		for (uint32_t i = 0; i < d3d11_quad_renderer_s::get_max_renderable_quads(); i++)
		{
			indicies.push_back(0 + (i * 4)); // Top left
			indicies.push_back(1 + (i * 4)); // Top right
			indicies.push_back(2 + (i * 4)); // Bottom right

			indicies.push_back(2 + (i * 4)); // Bottom right
			indicies.push_back(3 + (i * 4)); // Bottom left
			indicies.push_back(0 + (i * 4)); // Top left
		}

		index_buffer.allocate(indicies);

		// Allocate shaders
		d3d11_shader_load_info_t vertex_shader_load_info{};
		vertex_shader_load_info.src_code = vertex_shader_src;
		vertex_shader_load_info.shader_func_name = "v_main";
		vertex_shader_load_info.shader_profile = d3d11_shader_profiles::VERTEX_SHADER_PROFILE_V5;
		vertex_shader.load_from_string(vertex_shader_load_info);

		d3d11_shader_load_info_t pixel_shader_load_info{};
		pixel_shader_load_info.src_code = pixel_shader_src;
		pixel_shader_load_info.shader_func_name = "p_main";
		pixel_shader_load_info.shader_profile = d3d11_shader_profiles::PIXEL_SHADER_PROFILE_V5;
		pixel_shader.load_from_string(pixel_shader_load_info);

		// Return the sum of all the offsets
		auto progressive_offset =
			[&](uint32_t offset) -> uint32_t
			{
				static uint32_t offset_buffer = 0;
				offset_buffer += offset;
				return offset_buffer;
			};

		// Allocate input layout descriptor
		input_layout_descriptor.allocate(&vertex_shader,
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_offset(sizeof(glm::vec2)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0}
			}
		);

		// Allocate the blend state
		blend_state.allocate(nullptr);
	}

	void d3d11_quad_renderer_s::destroy()
	{
		vertex_buffer.destroy();
		index_buffer.destroy();
		input_layout_descriptor.destroy();
	}
}