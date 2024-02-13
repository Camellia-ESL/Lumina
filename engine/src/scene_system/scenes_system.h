#pragma once

#include "scene.h"

#include <vector>

namespace lumina
{
	// The class that handles every scene creation, destruction and activation
	// scenes should never be accessed or created without directly using this class. 
	// Get's created at application start after graphics initialization. (singleton)
	class scenes_system
	{
	public:

		scenes_system();

		static scenes_system& get_singleton() { return *instance_; }

		// Creates a scene
		bool create_scene(const std::string& scene_name);

		// Destroy a scene
		bool destroy_scene(const std::string& scene_name);

		// Change name to a scene
		bool change_name(const std::string& scene_name, const std::string& new_name);

		// Activate a scene
		void activate_scene(const std::string& scene_name);

		// Check if a given scene exist
		bool has_scene(const std::string& scene_name);

		// Get a given scene object
		scene* get_scene(const std::string& scene_name);

		// Gets the active scene (nullptr if there are no active scenes) 
		scene* get_active_scene() { return active_scene_; }

		// Wheter if there is a active scene or not
		bool has_active_scene() { return active_scene_ != nullptr; }

		// Wheter if the given scene is the current active one
		bool is_active_scene(scene* scene) { return active_scene_ == scene; }

		// Gets all the available scenes
		const std::vector<scene>& get_all_scenes() const { return scenes_; }

		// Render the active scene, it can only be called inside a rendering method.
		// It can only be called once.
		void render();

	private:

		static scenes_system* instance_;

	private:

		// The vector that contains all the scenes
		std::vector<scene> scenes_{};
		scene* active_scene_ = nullptr;

	};
}