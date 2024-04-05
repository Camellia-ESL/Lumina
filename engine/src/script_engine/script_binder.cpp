#include "script_binder.h"

#include "scene_system/scenes_system.h"
#include "mono_csharp_type_names.h"
#include "mono_type_utils.h"

#include "lumina.h"

#include "spdlog/spdlog.h"

namespace lumina
{
	mono_script* core_script_ref = nullptr;

	void script_binder::bind_all(mono_script* script_to_forward_binds)
	{
		core_script_ref = script_to_forward_binds;
		bind_scene_manager(script_to_forward_binds);
		bind_scene(script_to_forward_binds);
		bind_entity(script_to_forward_binds);
		bind_logger(script_to_forward_binds);
	}

#pragma region SceneManager

	static bool scene_manager_create_scene_func(MonoString* scene_name)
	{
		return scenes_system::get_singleton().create_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);
	}

	static bool scene_manager_get_scene_func(MonoString* scene_name, MonoObject** scene_out)
	{
		scene* scene_res = scenes_system::get_singleton().get_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);

		if (scene_res == nullptr)
			return false;

		MonoClass* scene_class = mono_object_get_class(*scene_out);
		MonoProperty* scene_name_prop = mono_class_get_property_from_name(
			scene_class, 
			lumina_csharp_namespace::scene_csharp_type::properties::NAME
		);

		// Assign the Scene Name
		MonoString* scene_name_value = core_script_ref->create_mono_str(scene_res->get_name());
		mono_property_set_value(scene_name_prop, *scene_out, (void**)&scene_name_value, nullptr);

		return true;
	}

	void script_binder::bind_scene_manager(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_manager_csharp_type::methods::CREATE_SCENE,
			lumina_csharp_namespace::scene_manager_csharp_type::TYPE_NAME,
			scene_manager_create_scene_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_manager_csharp_type::methods::GET_SCENE,
			lumina_csharp_namespace::scene_manager_csharp_type::TYPE_NAME,
			scene_manager_get_scene_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion
	
#pragma region Scene

	static void init_mono_entity(entity& entity_res, MonoObject* entity_out)
	{
		MonoClass* entity_class = mono_object_get_class(entity_out);

		// Get entity out fields and properties to assign
		MonoClassField* entity_id_field = mono_class_get_field_from_name(
			entity_class,
			lumina_csharp_namespace::entity_csharp_type::fields::_ID
		);

		MonoClassField* entity_registry_ptr_field = mono_class_get_field_from_name(
			entity_class,
			lumina_csharp_namespace::entity_csharp_type::fields::_REGISTRY_PTR
		);

		l_uint32 entity_id = (l_uint32)entity_res.get_entity();
		l_uint64 entity_registry_ptr = (l_uint64)entity_res.get_registry();

		// Assign the Entity Id
		mono_field_set_value(entity_out, entity_id_field, &entity_id);

		// Assign the Entity Registry Ptr
		mono_field_set_value(entity_out, entity_registry_ptr_field, &entity_registry_ptr);
	}

	static bool scene_create_entity_func(MonoString* scene_name, MonoObject** entity_out)
	{
		// Get's the scene
		scene* scene_res = scenes_system::get_singleton().get_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);

		if (scene_res == nullptr)
			return false;

		// Init the new entity
		entity entity_res = scene_res->create_entity();

		init_mono_entity(entity_res, *entity_out);

		return true;
	}

	static bool scene_get_entity_by_name_func(MonoString* scene_name, MonoString* entity_name, MonoObject** entity_out)
	{
		// Get's the scene
		scene* scene_res = scenes_system::get_singleton().get_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);
		
		if (scene_res == nullptr)
			return false;

		std::string entity_name_utf8 = mono_type_utils::mono_str_to_utf8_str(entity_name);

		// Get the scene entity registry 
		auto all_scene_entities = scene_res->get_entity_registry().view<identity_component>();

		// Loop thru all the entities trying to find one with the given name
		for (auto entity_ith : all_scene_entities)
		{
			entity entity_res{ &scene_res->get_entity_registry(), entity_ith };

			if (entity_res.get_component<identity_component>().name == entity_name_utf8)
			{
				init_mono_entity(entity_res, *entity_out);
				return true;
			}
		}

		return false;
	}

	static bool scene_destroy_entity_func(MonoString* scene_name, MonoObject* entity_to_destroy)
	{
		// Get's the scene
		scene* scene_res = scenes_system::get_singleton().get_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);

		if (scene_res == nullptr)
			return false;

		// Destroy the entity
		MonoClass* entity_class = mono_object_get_class(entity_to_destroy);

		MonoClassField* entity_id_field = mono_class_get_field_from_name(
			entity_class, 
			lumina_csharp_namespace::entity_csharp_type::fields::_ID
		);

		// Get the value of MyPublicFloatVar from the testingInstance object
		entt::entity entity_id;
		mono_field_get_value(entity_to_destroy, entity_id_field, &entity_id);
		scene_res->destroy_entity(entity_id);

		return true;
	}

	void script_binder::bind_scene(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_csharp_type::methods::CREATE_ENTITY,
			lumina_csharp_namespace::scene_csharp_type::TYPE_NAME,
			scene_create_entity_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_csharp_type::methods::GET_ENTITY_BY_NAME,
			lumina_csharp_namespace::scene_csharp_type::TYPE_NAME,
			scene_get_entity_by_name_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_csharp_type::methods::DESTROY_ENTITY,
			lumina_csharp_namespace::scene_csharp_type::TYPE_NAME,
			scene_destroy_entity_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion

#pragma region Entity

	static bool entity_get_component_func(entt::entity entity_id, entt::registry* entity_reg_ptr, MonoObject** component_out)
	{
		MonoObject* component_out_ref = *component_out;

		if (entity_reg_ptr == nullptr)
			return false;

		// Construct the requested entity
		entity entity_req = entity(entity_reg_ptr, entity_id);

		// Get the component class
		MonoClass* component_class = mono_object_get_class(component_out_ref);
		std::string component_class_name = mono_class_get_name(component_class);

		// *Identifier Class*
		if (component_class_name == lumina_csharp_namespace::identifier_csharp_type::TYPE_NAME)
		{
			// Get entity out fields and properties to assign
			MonoProperty* component_id_prop = mono_class_get_property_from_name(
				component_class,
				"Id"
			);

			MonoProperty* component_name_prop = mono_class_get_property_from_name(
				component_class,
				"Name"
			);

			identity_component& identifier = entity_req.get_component<identity_component>();

			// Assign the Component Id
			MonoString* component_id_value = core_script_ref->create_mono_str(identifier.id);
			mono_property_set_value(component_id_prop, component_out_ref, (void**)&component_id_value, nullptr);

			// Assign the Component Name
			MonoString* component_name_value = core_script_ref->create_mono_str(identifier.name);
			mono_property_set_value(component_name_prop, component_out_ref, (void**)&component_name_value, nullptr);
		}

		return true;
	}

	void script_binder::bind_entity(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::entity_csharp_type::methods::GET_COMPONENT,
			lumina_csharp_namespace::entity_csharp_type::TYPE_NAME,
			entity_get_component_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
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