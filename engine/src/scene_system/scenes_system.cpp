#include "scenes_system.h"

#include "graphics/renderer_2d.h"
#include "components/components.h"

lumina::scenes_system* lumina::scenes_system::singleton_instance_ = nullptr;

namespace lumina
{
	bool scenes_system::create_scene(const std::string& scene_name)
	{
		// Check if a scene with the given name already exist
		if (has_scene(scene_name))
			return false;

		// Create the scene and calls the callbacks
		scene new_scene{ scene_name };

		// Add the scene to the scene system 
		scenes_.push_back(std::move(new_scene));

		return true;
	}

	bool scenes_system::destroy_scene(const std::string& scene_name)
	{
		if (!has_scene(scene_name))
			return false;

		scene* scene_to_destroy = get_scene(scene_name);

		// Destroy the scene
		if (active_scene_ == scene_to_destroy)
			active_scene_ = nullptr;

		// Creates an itherator to iterate the list safely
		std::vector<scene>::iterator scene_it = scenes_.begin();

		// Search for missing items and delete them
		while (scene_it != scenes_.end())
		{
			if (scene_it->get_name() == scene_name)
				scene_it = scenes_.erase(scene_it);
			else
				scene_it++;
		}

		return true;
	}

	bool scenes_system::change_name(const std::string& scene_name, const std::string& new_name)
	{
		// Check if the scene to change doesn't exist
		if (!has_scene(scene_name))
			return false;

		// Check if another scene with this name already exist
		if (has_scene(new_name))
			return false;

		// Set the new scene name
		get_scene(scene_name)->set_name(new_name);

		return true;
	}

	void scenes_system::activate_scene(const std::string& scene_name)
	{
		if (!has_scene(scene_name))
			return;

		scene* scene_to_activate = get_scene(scene_name);

		// Set the scene pointer as the active scene pointer
		active_scene_ = scene_to_activate;
	}

	bool scenes_system::has_scene(const std::string& scene_name)
	{
		for (size_t i = 0; i < scenes_.size(); i++)
			if (scenes_[i].get_name() == scene_name)
				return true;

		return false;
	}

	scene* scenes_system::get_scene(const std::string& scene_name)
	{
		for (size_t i = 0; i < scenes_.size(); i++)
			if (scenes_[i].get_name() == scene_name)
				return &scenes_[i];

		return nullptr;
	}

	void scenes_system::render()
	{
		// Check if there is not an active scene
		if (!has_active_scene())
			return;

		render(get_active_scene()->get_camera());
	}

	void scenes_system::render(camera_component* camera)
	{
		// Check if the camera is null
		if (camera == nullptr)
			return;

		// Check if there is not an active scene
		if (!has_active_scene())
			return;

		// Get the active scene 
		scene* active_scene = get_active_scene();
		entt::registry& scene_registry = active_scene->get_entity_registry();

		// Draw Sprites 
		renderer_2d_s::begin_render_pass(camera);

		auto sprites = active_scene->get_entity_registry().view<
			transform_component,
			sprite_component
		>();

		for (auto ent : sprites)
		{
			entity sprite_entity{ &scene_registry, ent };

			transform_component& transform = sprite_entity.get_component<transform_component>();
			sprite_component& sprite = sprite_entity.get_component<sprite_component>();

			renderer_2d_s::draw_quad(transform.get_model_matrix(), sprite.color);
		}

		renderer_2d_s::end_render_pass();
	}
}