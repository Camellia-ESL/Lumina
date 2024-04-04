#include "script_binder.h"

#include "scene_system/scenes_system.h"
#include "mono_csharp_type_names.h"
#include "mono_type_utils.h"

#include "lumina.h"

#include "spdlog/spdlog.h"

namespace lumina
{
	void script_binder::bind_all(mono_script* script_to_forward_binds)
	{
		bind_scene_manager(script_to_forward_binds);
		bind_scene(script_to_forward_binds);
		bind_logger(script_to_forward_binds);
	}

#pragma region SceneManager

	static bool scene_manager_create_scene_func(MonoString* scene_name)
	{
		return lumina::scenes_system::get_singleton().create_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);
	}

	static MonoObject* scene_manager_get_scene_func(MonoString* scene_name)
	{

	}

	void script_binder::bind_scene_manager(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_manager_csharp_type::methods::CREATE_SCENE,
			lumina_csharp_namespace::scene_manager_csharp_type::TYPE_NAME,
			scene_manager_create_scene_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion
	
#pragma region Scene

	void script_binder::bind_scene(mono_script* script_to_forward_binds)
	{

	}

#pragma endregion

#pragma region Logger

	static void logger_log_info_func(MonoString* msg)
	{
		spdlog::info(mono_type_utils::mono_str_to_utf8_str(msg));
	}

	static void logger_log_warning_func(MonoString* msg)
	{
		spdlog::warn(mono_type_utils::mono_str_to_utf8_str(msg));
	}

	static void logger_log_error_func(MonoString* msg)
	{
		spdlog::error(mono_type_utils::mono_str_to_utf8_str(msg));
	}

	void script_binder::bind_logger(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::logger_csharp_type::methods::LOG_INFO,
			lumina_csharp_namespace::logger_csharp_type::TYPE_NAME,
			logger_log_info_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::logger_csharp_type::methods::LOG_WARNING,
			lumina_csharp_namespace::logger_csharp_type::TYPE_NAME,
			logger_log_warning_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::logger_csharp_type::methods::LOG_ERROR,
			lumina_csharp_namespace::logger_csharp_type::TYPE_NAME,
			logger_log_error_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion

}