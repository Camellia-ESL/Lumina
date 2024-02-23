#pragma once

#include "ui/view.h"

#include "lumina.h"

namespace lumina_editor
{
	class scene_grid_view : public view
	{
	public:

		void on_create() override;
		void on_render() override;

	private:

		glm::mat4 grid_matrix_{ 1.0f };
		float grid_size_ = 3000.0f;

	};
}