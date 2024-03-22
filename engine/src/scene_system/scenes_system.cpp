#include "scenes_system.h"

#include "event_system/event_system.h"
#include "graphics/renderer_2d.h"
#include "components/components.h"

lumina::scenes_system* lumina::scenes_system::singleton_instance_ = nullptr;

namespace lumina
{
	scenes_system::scenes_system()
	{
		init();
	}

	bool scenes_system::create_scene(const std::string& scene_name)
	{
		// Check if a scene with the given name already exist
		if (has_scene(scene_name))
			return false;

		// Add the scene to the scene system 
		scenes_.push_back(std::make_shared<scene>(scene_name));

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
		std::vector<std::shared_ptr<scene>>::iterator scene_it = scenes_.begin();

		// Search for missing items and delete them
		while (scene_it != scenes_.end())
		{
			if (scene_it->get()->get_name() == scene_name)
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

	void scenes_system::destroy_all()
	{
		// Set the active scene to nullptr
		active_scene_ = nullptr;

		// Destroys all the scenes
		scenes_.clear();
	}

	bool scenes_system::has_scene(const std::string& scene_name)
	{
		for (size_t i = 0; i < scenes_.size(); i++)
			if (scenes_[i]->get_name() == scene_name)
				return true;

		return false;
	}

	scene* scenes_system::get_scene(const std::string& scene_name)
	{
		for (size_t i = 0; i < scenes_.size(); i++)
			if (scenes_[i]->get_name() == scene_name)
				return scenes_[i].get();

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

		auto sprites = scene_registry.view<
			transform_component,
			sprite_component
		>();

		for (auto ent : sprites)
		{
			entity sprite_entity{ &scene_registry, ent };

			transform_component& transform = sprite_entity.get_component<transform_component>();
			sprite_component& sprite = sprite_entity.get_component<sprite_component>();

			if(sprite.has_texture() && sprite.get_texture()->is_allocated())
				renderer_2d_s::draw_quad(transform.get_model_matrix(), *sprite.get_texture());
			else 
				renderer_2d_s::draw_quad(transform.get_model_matrix(), sprite.color);
		}

		renderer_2d_s::end_render_pass();
	}

	void scenes_system::init()
	{
		// Install an event to handle window resize (recalculate all the cameras projections)
		event_listener::get_singleton().submit_event_callback(
			[&](const window_resize_event_t& resize_event) -> void 
			{
				// Check that sizes aren't null
				if (resize_event.app_width <= 0 || resize_event.app_height <= 0)
					return;

				for (auto& scene : scenes_)
				{
					auto cameras = scene->get_entity_registry().view<camera_component>();
					for (auto camera_entity : cameras)
					{
						entity camera{ &scene->get_entity_registry(), camera_entity };
						camera.get_component<camera_component>().recalculate_all_matricies();
					}
				}
			}
		);
	}
}