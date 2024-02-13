#include "scenes_visualizer_view.h"

#include "../editor_compile_configs.h"

#include "ui/view_register.h"
#include "scene_hierarchy_view.h"
#include "scene_editor_view.h"

#include "scene_system/scenes_system.h"

#include "spdlog/spdlog.h"

#include "ImGui/imgui.h"

namespace lumina_editor
{
	void scenes_visualizer_view::on_render()
	{
		ImGui::Begin("Scenes Visualizer");

		lumina::scenes_system& scene_system = lumina::scenes_system::get_singleton();
		static const lumina::scene* selected_scene = nullptr;
		static std::shared_ptr<scene_hierarchy_view> scene_hierarchy = nullptr;
		static std::shared_ptr<scene_editor_view> scene_editor = nullptr;

		const auto destroy_scene_view_context =
			[&]() -> void
			{
				// If there was another scene hierarchy view opened, destroy's it 
				if (scene_hierarchy != nullptr)
					view_register_s::destroy_view(scene_hierarchy);

				// If there was another scene editor view opened, destroy's it 
				if (scene_editor != nullptr)
					view_register_s::destroy_view(scene_editor);
			};

		// Add Scene Button
		if (ImGui::SmallButton("Add Scene"))
		{
			static int new_scene_id = 0;
			new_scene_id++;

			destroy_scene_view_context();
			selected_scene = nullptr;

			// Create's the new scene
			scene_system.create_scene("Untitled - " + std::to_string(new_scene_id));
		}

		// Display scenes 
		for (auto& scene : scene_system.get_all_scenes())
		{ 
			// Check if the scene is the selected one
			bool is_scene_selected = false;
			if (selected_scene == &scene)
				is_scene_selected = true;

			// Handle scene on click
			if (ImGui::Selectable(scene.get_name().c_str(), is_scene_selected))
			{
				selected_scene = &scene;

				destroy_scene_view_context();

				// Create's the new scene hierarchy 
				scene_hierarchy = std::make_shared<scene_hierarchy_view>(const_cast<lumina::scene*>(&scene));
				view_register_s::register_view(scene_hierarchy);

				// Create's the new scene editor
				scene_editor = std::make_shared<scene_editor_view>(const_cast<lumina::scene*>(&scene));
				view_register_s::register_view(scene_editor);
			}
		}

		ImGui::End();
	}
}