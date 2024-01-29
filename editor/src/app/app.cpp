#include "app.h"

#include "ui/ui_render.h"

#include "lumina.h"

namespace lumina_editor
{
	void editor_app_player::on_init()
	{
		// TESTING PURPOSE ONLY
		lumina::d3d11_vertex_buffer vertex_buffer{};

		// Allocate vertex buffer for quad 2d
		lumina::d3d11_vertex_buffer_alloc_info_t vertex_buffer_alloc_info{};
		vertex_buffer_alloc_info.buffer_size = sizeof(float) * 30;
		vertex_buffer_alloc_info.data_stride = sizeof(float);

		vertex_buffer.allocate(vertex_buffer_alloc_info);
		vertex_buffer.enable();

		// Allocate shaders for quad 2d
		lumina::d3d11_vertex_shader vertex_shader{};
		lumina::d3d11_shader_load_info_t vertex_shader_load_info{};
		vertex_shader_load_info.file_path_name = "resources/examples/shader_examples/d3d11_shaders/quad_shader.hlsl";
		vertex_shader_load_info.shader_func_name = "vertex_shader_main";
		vertex_shader_load_info.shader_profile = lumina::d3d11_shader_profiles::VERTEX_SHADER_PROFILE_V5;
		
		vertex_shader.load_from_file(vertex_shader_load_info);
		vertex_shader.enable();

		// -- TESTING PURPOSE ONLY -- 

		// Inits UI Rendering
		ui_render_s::on_init();
	}

	void editor_app_player::on_update()
	{
		
	}

	void editor_app_player::on_render()
	{
		ui_render_s::on_render();
	}
}