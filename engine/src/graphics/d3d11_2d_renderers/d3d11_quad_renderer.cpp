#include "d3d11_quad_renderer.h"

#include "../d3d11_api/d3d11_api.h"

namespace lumina
{
	static const std::string vertex_shader_src = R"(
	
		cbuffer generic_constant_buffer : register(b0)
		{
			float4x4 projection_matrix;
			float4x4 view_matrix;
		};

		struct vertex_output
		{ 
			float4 position : SV_POSITION; 
			float4 color : COLOR;
			float2 texture_coordinates : TEXTURE_COORDINATES;
			uint texture_slot : TEXTURE_SLOT; 
			bool is_textured : IS_TEXTURED;
		};
	
		vertex_output v_main(
			float2 position : POSITION, 
			float4x4 model : MODEL_TRANSFORM, 
			float4 color : COLOR, 
			float2 texture_coord : TEXTURE_COORDINATES,
			uint texture_slot : TEXTURE_SLOT,
			bool is_textured : IS_TEXTURED
		)
		{
			vertex_output output;
			output.position = mul(float4(position, 0.0f, 1.0f), mul(model, mul(view_matrix, projection_matrix)));
			output.color = color;
			output.texture_coordinates = texture_coord;
			output.texture_slot = texture_slot;
			output.is_textured = is_textured;

			return output;
		}

	)";

	static const std::string pixel_shader_src = R"(

		Texture2D obj_texture0 : register(t0);
		Texture2D obj_texture1 : register(t1);
		Texture2D obj_texture2 : register(t2);
		Texture2D obj_texture3 : register(t3);
		Texture2D obj_texture4 : register(t4);
		Texture2D obj_texture5 : register(t5);
		Texture2D obj_texture6 : register(t6);
		Texture2D obj_texture7 : register(t7);
		SamplerState obj_sampler_state : register(s0);

		float4 p_main(
			float4 position : SV_POSITION, 
			float4 color : COLOR, 
			float2 texture_coord : TEXTURE_COORDINATES,
			uint texture_slot : TEXTURE_SLOT,
			bool is_textured : IS_TEXTURED
		) : SV_Target
		{
			float4 color_output;

			if(is_textured)
			{
				if(texture_slot == 0)
					color_output = obj_texture0.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 1)
					color_output = obj_texture1.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 2)
					color_output = obj_texture2.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 3)
					color_output = obj_texture3.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 4)
					color_output = obj_texture4.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 5)
					color_output = obj_texture5.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 6)
					color_output = obj_texture6.Sample(obj_sampler_state, texture_coord);
				if(texture_slot == 7)
					color_output = obj_texture7.Sample(obj_sampler_state, texture_coord);
			}
			else 
				color_output = color;

			return color_output;
		}

	)";
		
	struct quad_vertex_t
	{
		// Static quad position that will be multiplied by the transform
		glm::vec2 position;
		
		// The model transform that will be used to multiply the position
		glm::mat4 model_transform;

		// The quad color
		glm::vec4 color;

		// The quad texture coordinates
		glm::vec2 texture_coordinates;

		// The texture slot
		uint32_t texture_slot;

		// Wheter if the quad is textured or not
		bool is_textured;
	};

	struct alignas(16) generic_constant_buffer_t
	{
		// A orthographic or a perspective projection matrix
		glm::mat4 projection_matrix{ glm::mat4(1.0f) };

		// A view matrix (the camera matrix)
		glm::mat4 view_matrix{ glm::mat4(1.0f) };
	};

	static d3d11_vertex_buffer q_vertex_buffer{};
	static d3d11_index_buffer q_index_buffer{};
	static d3d11_vertex_shader q_vertex_shader{};
	static d3d11_pixel_shader q_pixel_shader{};
	static d3d11_input_layout_descriptor q_input_layout_descriptor{};
	static d3d11_blend_state q_blend_state{};
	static d3d11_constant_buffer q_generic_constant_buffer{};
	static d3d11_sampler q_texture_sampler{};
	static d3d11_rasterizer q_rasterizer{};

	static std::vector<quad_vertex_t> quads_verticies{};
	static std::vector<d3d11_texture*> textures_submitted{};
	static generic_constant_buffer_t generic_constant_buffer_data{};
	static uint32_t rendered_quads_this_frame = 0;
	static camera_component* camera_this_frame = nullptr;
	static const uint32_t verticies_per_quad = 4;
	static const uint32_t indicies_per_quad = 6;

	static bool has_texture_been_submitted(d3d11_texture* texture_ptr) 
	{ 
		return std::find(textures_submitted.begin(), textures_submitted.end(), texture_ptr) != textures_submitted.end();
	}

	static uint32_t get_texture_slot(d3d11_texture* texture_ptr)
	{
		for (uint32_t i = 0; i < textures_submitted.size(); i++)
			if (textures_submitted[i] == texture_ptr)
				return i;

		return 0;
	}
	
	void d3d11_quad_renderer_s::begin_render_pass(camera_component* camera)
	{
		// Clear the previous render pass
		quads_verticies.clear();
		textures_submitted.clear();
		rendered_quads_this_frame = 0;
		
		// Assert that the camera exist
		if (camera == nullptr)
			return;
		
		camera_this_frame = camera;

		generic_constant_buffer_data.view_matrix = camera_this_frame->get_view_matrix();
		generic_constant_buffer_data.projection_matrix = camera_this_frame->get_projection_matrix();

		// Traspose matricies contained in the constant buffer
		generic_constant_buffer_data.view_matrix = glm::transpose(generic_constant_buffer_data.view_matrix);
		generic_constant_buffer_data.projection_matrix = glm::transpose(generic_constant_buffer_data.projection_matrix);
	}

	void d3d11_quad_renderer_s::end_render_pass()
	{
		if (rendered_quads_this_frame <= 0)
			return;

		// Enable all the d3d11 resources needed to render the quad
		q_vertex_buffer.enable();
		q_index_buffer.enable();
		q_vertex_shader.enable();
		q_pixel_shader.enable();
		q_input_layout_descriptor.enable();
		q_blend_state.enable();
		q_generic_constant_buffer.enable();
		q_texture_sampler.enable();
		q_rasterizer.enable();

		for (size_t i = 0; i < textures_submitted.size(); i++)
			textures_submitted[i]->enable(i);

		// Load the vertex buffer with the verticies of this render pass
		q_vertex_buffer.load_data(&quads_verticies[0], sizeof(quad_vertex_t) * quads_verticies.size());

		// Load the constant buffer with the updated data
		q_generic_constant_buffer.load_data(&generic_constant_buffer_data, sizeof(generic_constant_buffer_t));

		// Draw call, render all the quads
		d3d11_instance::get_singleton().get_device_context()->DrawIndexed(rendered_quads_this_frame * indicies_per_quad, 0, 0);
	}

	void d3d11_quad_renderer_s::draw_quad(const glm::mat4& quad_transform, const glm::vec4& color)
	{
		if (rendered_quads_this_frame >= MAX_RENDERABLE_QUADS_)
		{
			end_render_pass();
			begin_render_pass(camera_this_frame);
		}

		glm::mat4 transposed_transform = glm::transpose(quad_transform);

		quads_verticies.push_back({ { -0.5f,  0.5f }, transposed_transform, color, { 0.0f, 0.0f }, 0 , false }); // Top left
		quads_verticies.push_back({ {  0.5f,  0.5f }, transposed_transform, color, { 0.0f, 0.0f }, 0 , false }); // Top right
		quads_verticies.push_back({ {  0.5f, -0.5f }, transposed_transform, color, { 0.0f, 0.0f }, 0 , false }); // Bottom right
		quads_verticies.push_back({ { -0.5f, -0.5f }, transposed_transform, color, { 0.0f, 0.0f }, 0 , false }); // Bottom left

		rendered_quads_this_frame++;
	}

	void d3d11_quad_renderer_s::draw_quad(const glm::mat4& quad_transform, const d3d11_texture& texture)
	{
		const bool has_texture_to_submit = !has_texture_been_submitted(const_cast<d3d11_texture*>(&texture));

		// Check if we have reched the textures slot limit, draw everything and begin a new clean render pass
		if (textures_submitted.size() >= MAX_TEXTURES_SLOT_ && has_texture_to_submit)
		{
			end_render_pass();
			begin_render_pass(camera_this_frame);
		}

		// Check if the texture is new and is not already been submitted
		if (has_texture_to_submit)
			textures_submitted.push_back(const_cast<d3d11_texture*>(&texture));

		const uint32_t texture_slot = get_texture_slot(const_cast<d3d11_texture*>(&texture));

		// Check if we have reched the quad limit, draw everything and begin a new clean render pass
		if (rendered_quads_this_frame >= MAX_RENDERABLE_QUADS_)
		{
			end_render_pass();
			begin_render_pass(camera_this_frame);
		}

		glm::mat4 transposed_transform = glm::transpose(quad_transform);

		quads_verticies.push_back({ { -0.5f,  0.5f }, transposed_transform, { 0.0f , 0.0f , 0.0f , 0.0f }, { 0.0f, 0.0f }, texture_slot, true }); // Top left
		quads_verticies.push_back({ {  0.5f,  0.5f }, transposed_transform, { 0.0f , 0.0f , 0.0f , 0.0f }, { 1.0f, 0.0f }, texture_slot, true }); // Top right
		quads_verticies.push_back({ {  0.5f, -0.5f }, transposed_transform, { 0.0f , 0.0f , 0.0f , 0.0f }, { 1.0f, 1.0f }, texture_slot, true }); // Bottom right
		quads_verticies.push_back({ { -0.5f, -0.5f }, transposed_transform, { 0.0f , 0.0f , 0.0f , 0.0f }, { 0.0f, 1.0f }, texture_slot, true }); // Bottom left

		rendered_quads_this_frame++;
	}

	void d3d11_quad_renderer_s::init()
	{
		// Allocate vertex buffer
		d3d11_vertex_buffer_alloc_info_t vertex_buffer_alloc_info{};
		vertex_buffer_alloc_info.buffer_size = d3d11_quad_renderer_s::get_max_renderable_quads() * (verticies_per_quad * sizeof(quad_vertex_t));
		vertex_buffer_alloc_info.data_stride = sizeof(quad_vertex_t);
		vertex_buffer_alloc_info.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		q_vertex_buffer.allocate(vertex_buffer_alloc_info);

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

		q_index_buffer.allocate(indicies);

		// Allocate shaders
		d3d11_shader_load_info_t vertex_shader_load_info{};
		vertex_shader_load_info.src_code = vertex_shader_src;
		vertex_shader_load_info.shader_func_name = "v_main";
		vertex_shader_load_info.shader_profile = d3d11_shader_profiles::VERTEX_SHADER_PROFILE_V5;
		q_vertex_shader.load_from_string(vertex_shader_load_info);

		d3d11_shader_load_info_t pixel_shader_load_info{};
		pixel_shader_load_info.src_code = pixel_shader_src;
		pixel_shader_load_info.shader_func_name = "p_main";
		pixel_shader_load_info.shader_profile = d3d11_shader_profiles::PIXEL_SHADER_PROFILE_V5;
		q_pixel_shader.load_from_string(pixel_shader_load_info);

		// Return the sum of all the offsets
		auto progressive_descriptor_memory_offset =
			[&](uint32_t offset) -> uint32_t
			{
				static uint32_t offset_buffer = 0;
				offset_buffer += offset;
				return offset_buffer;
			};

		// Allocate input layout descriptor
		q_input_layout_descriptor.allocate(
			&q_vertex_shader,
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec2)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "MODEL_TRANSFORM", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "TEXTURE_COORDINATES", 0, DXGI_FORMAT_R32G32_FLOAT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec4)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "TEXTURE_SLOT", 0, DXGI_FORMAT_R32_UINT, 0, progressive_descriptor_memory_offset(sizeof(glm::vec2)), D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "IS_TEXTURED", 0, DXGI_FORMAT_R8_UINT, 0, progressive_descriptor_memory_offset(sizeof(uint32_t)), D3D11_INPUT_PER_VERTEX_DATA, 0}
			}
		);

		// Allocate the blend state
		q_blend_state.allocate(nullptr);

		// Allocate the constant buffer
		q_generic_constant_buffer.allocate(sizeof(generic_constant_buffer_t));

		// Allocate the texture sampler
		q_texture_sampler.allocate();

		// Allocate the default rasterizer
		q_rasterizer.allocate();
	}

	void d3d11_quad_renderer_s::destroy()
	{
		q_vertex_buffer.destroy();
		q_index_buffer.destroy();
		q_input_layout_descriptor.destroy();
		q_rasterizer.destroy();
	}
}