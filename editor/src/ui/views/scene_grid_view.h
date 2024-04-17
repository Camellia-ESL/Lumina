#pragma once

#include "ui/view.h"

#include "lumina.h"

namespace lumina_editor
{
	class scene_grid_view : public view
	{
	public:

		void on_render() override;

	private:

		lumina::transform_component grid_transform_{};
		float grid_size_ = 500.0f;
		glm::vec4 grid_color_ = { 1.0f , 1.0f , 1.0f , 0.4f };

	};
}