#pragma once

#include "ui/view.h"
#include "entity_editor_view.h"

#include "lumina.h"

namespace lumina_editor
{
	class scene_hierarchy_view : public view
	{
	public:

		scene_hierarchy_view(lumina::scene* scene) : scene_{ scene } {}

		void on_render() override;
		void on_destroy() override;

	private:

		lumina::scene* scene_;
		lumina::entity selected_entity_;
		std::shared_ptr<entity_editor_view> entity_editor_view_;
		
		void render_properties_popup();
		void render_entities();

	};
}