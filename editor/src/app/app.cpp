#include "app.h"

#include "ui/ui_render.h"

#include "lumina.h"

namespace lumina_editor
{
	void editor_app_player::on_init()
	{
		lumina::d3d11_vertex_buffer vertex_buffer{};

		lumina::d3d11_vertex_buffer_alloc_info_t vertex_buffer_alloc_info{};
		vertex_buffer_alloc_info.buffer_size = sizeof(float) * 30;
		vertex_buffer_alloc_info.data_stride = sizeof(float);

		vertex_buffer.allocate(vertex_buffer_alloc_info);
		vertex_buffer.enable();

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