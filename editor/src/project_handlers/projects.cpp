#include "projects.h"

#include "../editor_compile_configs.h"
#include "ui/view_register.h"
#include "assets_serializer.h"

#include "core/lumina_file_system.h"

#include "yaml-cpp/yaml.h"
#include "spdlog/spdlog.h"

LUMINA_SINGLETON_DECL_INSTANCE(lumina_editor::project_handler);

namespace lumina_editor
{
	void project_handler::create_project(const std::string& directory_path, const std::string& project_name)
	{
		// If a project is already loaded unloads it first
		if (has_opened_project())
			unload_project();
		else
		{
			destroy_scenes_context();
			destroy_assets();
		}

		// Log the save msg
		spdlog::warn("Creating new project...");

		// Create's a new project object and assign it to loaded project
		loaded_project_ = std::make_shared<project>();
		loaded_project_->name = project_name;
		loaded_project_->scenes_dir_path = LUMINA_EDITOR_PROJECT_SCENES_DEFAULT_PATH;
		loaded_project_->project_dir_path = directory_path + "\\" + project_name;

		// Set the content browser directory
		content_browser_.set_content_directory(loaded_project_->project_dir_path);

		// Create's the projects folders
		lumina::lumina_file_system_s::create_folder(directory_path + "\\" + project_name);
		lumina::lumina_file_system_s::create_folder(directory_path + "\\" + project_name + "\\" + LUMINA_EDITOR_PROJECT_SCENES_DEFAULT_PATH);
		lumina::lumina_file_system_s::create_folder(directory_path + "\\" + project_name + "\\" + LUMINA_EDITOR_PROJECT_ASSETS_DEFAULT_PATH);

		// Create's an empty scene and loads it
		lumina::scenes_system::get_singleton().create_scene("Untitled Scene");

		// Save the project
		save_project();

		spdlog::info("Project Created");
	}

	void project_handler::save_project()
	{
		spdlog::warn("Saving project...");

		// Save the project settings
		save_project_settings();

		// Serialize all the assets in the project
		save_assets();

		// Serialize all the scenes in the project
		save_scenes();

		spdlog::info("Project saved...");
	}

	bool project_handler::load_project(const std::string& project_file)
	{
		// If a project is already loaded unloads it first
		if (has_opened_project())
			unload_project();
		else
		{
			destroy_scenes_context();
			destroy_assets();
		}

		// Tries first to deserialize project settings
		YAML::Node scene_yaml;

		try
		{
			scene_yaml = YAML::LoadFile(project_file);
		}
		catch (const std::exception&)
		{
			return false;
		}

		// Check if the file isn't good
		if (!scene_yaml || !scene_yaml["Project Name"] || !scene_yaml["Scenes Path"])
			return false;

		// Load project metadata
		loaded_project_ = std::make_shared<project>();
		loaded_project_->name = scene_yaml["Project Name"].as<std::string>();
		loaded_project_->scenes_dir_path = scene_yaml["Scenes Path"].as<std::string>();
		loaded_project_->project_dir_path = lumina::lumina_file_system_s::get_file_directory(project_file);

		// Set the content browser directory
		content_browser_.set_content_directory(loaded_project_->project_dir_path);

		// Tries to deserialize assets (assets must be deserialized first before scenes)
		load_assets();

		// Tries to deserialize scenes
		load_scenes();

		return true;
	}

	void project_handler::unload_project()
	{
		// Skip if there is not a loaded project
		if (!has_opened_project())
			return;

		// Save the project first
		save_project();

		// Cleanup the scene context
		destroy_scenes_context();

		// Destroy's all the assets that belongs to the project
		destroy_assets();

		// Unloads the project
		loaded_project_.reset();
		loaded_project_ = nullptr;
	}

	void project_handler::save_project_settings()
	{
		YAML::Emitter yaml_stream_emitter;
		yaml_stream_emitter << YAML::BeginMap;
		yaml_stream_emitter << YAML::Key << "Project Name";
		yaml_stream_emitter << YAML::Value << loaded_project_->name;
		yaml_stream_emitter << YAML::Key << "Scenes Path";
		yaml_stream_emitter << YAML::Value << loaded_project_->scenes_dir_path;
		yaml_stream_emitter << YAML::EndMap;

		std::ofstream out_stream{ loaded_project_->project_dir_path + "\\" + loaded_project_->name + ".lmproj" };
		out_stream << yaml_stream_emitter.c_str();
	}

	void project_handler::save_scenes()
	{
		lumina::scenes_system& scene_system = lumina::scenes_system::get_singleton();

		for (auto& scene : scene_system.get_all_scenes())
		{
			if (scene == nullptr)
				continue;

			lumina::scene_serializer::serialize_yaml(
				scene.get(),
				loaded_project_->project_dir_path + "\\" + loaded_project_->scenes_dir_path + "\\" + scene->get_name() + ".scene"
			);
		}
	}

	void project_handler::save_assets()
	{
		assets_serializer::serialize_assets_bundle(
			lumina::asset_atlas::get_singleton().get_registry().get_registry(), 
			loaded_project_->project_dir_path + "\\" + loaded_project_->name + ".lmbundle"
		);
	}

	void project_handler::load_scenes()
	{
		std::vector<std::string> scene_files_path =
			lumina::lumina_file_system_s::get_files_in_directory(
				loaded_project_->project_dir_path + "\\" + loaded_project_->scenes_dir_path
			);

		// Log the save msg
		spdlog::info("Importing scenes...");

		for (auto& path : scene_files_path)
		{
			lumina::scenes_system::get_singleton().create_scene("__importing_scene__");
			lumina::scene_serializer::deserialize_yaml(
				lumina::scenes_system::get_singleton().get_scene("__importing_scene__"),
				path
			);
		}
	}

	void project_handler::load_assets()
	{
		assets_serializer::deserialize_assets_bundle(
			lumina::asset_atlas::get_singleton().get_registry(),
			loaded_project_->project_dir_path + "\\" + loaded_project_->name + ".lmbundle"
		);
	}

	void project_handler::destroy_scenes_context()
	{
		// Destroy's all the scenes
		lumina::scenes_system::get_singleton().destroy_all();

		// Destroy's all the editor views that belongs to scenes
		view_register_s::destroy_views("scene_view_type");
	}

	void project_handler::destroy_assets()
	{
		// Destroy's all the loaded assets
		lumina::asset_atlas::get_singleton().get_registry().clear();
	}
}