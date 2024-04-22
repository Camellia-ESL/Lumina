#include "script_binder.h"

#include "scene_system/scenes_system.h"
#include "mono_csharp_type_names.h"
#include "mono_type_utils.h"

#include "lumina.h"

#include "spdlog/spdlog.h"

// Security checks disabled (fastest execution)
#define LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_DISABLED 0
// Security checks slightly decreased (fast execution)
#define LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_FAST 1
// Security checks on (normal execution)
#define LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX 2

// Defines the level of security checks inside the code, this can slightly increase or decrease performance * safety
#define LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

namespace lumina
{
	mono_script* core_script_ref = nullptr;

	void script_binder::bind_all(mono_script* script_to_forward_binds)
	{
		core_script_ref = script_to_forward_binds;
		bind_application(script_to_forward_binds);
		bind_event_handler(script_to_forward_binds);
		bind_scene_manager(script_to_forward_binds);
		bind_scene(script_to_forward_binds);
		bind_entity(script_to_forward_binds);
		bind_transform(script_to_forward_binds);
		bind_sprite(script_to_forward_binds);
		bind_logger(script_to_forward_binds);
	}

#pragma region Application

	static float application_get_delta_time_func()
	{
		return application_player::get_singleton().get_delta_time();
	}

	void script_binder::bind_application(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::application_csharp_type::methods::GET_DELTA_TIME,
			lumina_csharp_namespace::application_csharp_type::TYPE_NAME,
			application_get_delta_time_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion

#pragma region Event Handler

	static bool event_handler_is_key_pressed_func(keyboard_keys_types_e key)
	{
		return event_state_handler_s::is_key_pressed(key);
	}

	static bool event_handler_is_key_released_func(keyboard_keys_types_e key)
	{
		return event_state_handler_s::is_key_released(key);
	}

	static bool event_handler_is_key_held_func(keyboard_keys_types_e key)
	{
		return event_state_handler_s::is_key_held(key);
	}

	static void event_handler_register_event_callback_func(MonoObject* callback)
	{
		// Get the component class
		MonoClass* callback_class = mono_object_get_class(callback);
		std::string callback_class_name = mono_class_get_name(callback_class);

		// Submit the event registration
		
		// *KeyboardEventCallback Class*
		if (callback_class_name == lumina_csharp_namespace::keyboard_event_callback_type::TYPE_NAME)
		{
			event_listener::get_singleton().submit_event_callback(
				[=](const keyboard_event_t& e) -> void
				{
					// Get the keyboard event callback event holder
					MonoClassField* event_field = mono_class_get_field_from_name(
						callback_class,
						lumina_csharp_namespace::keyboard_event_callback_type::fields::_EVENT
					);

					// Get's the event object
					MonoObject* event_object;
					mono_field_get_value(callback, event_field, &event_object);
					MonoClass* event_object_class = mono_object_get_class(event_object);

					MonoClassField* event_type_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::event_base_type::fields::_EVENT_TYPE
					);

					MonoClassField* event_action_type_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::keyboard_event_type::fields::_ACTION_TYPE
					);

					MonoClassField* event_key_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::keyboard_event_type::fields::_KEY
					);

					MonoClassField* event_key_mod_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::keyboard_event_type::fields::_KEY_MOD
					);

					// Set the values for the current event happened in the event object
					mono_field_set_value(event_object, event_type_field, (void*)&e.event_type);
					mono_field_set_value(event_object, event_action_type_field, (void*)&e.action_type);
					mono_field_set_value(event_object, event_key_field, (void*)&e.key);
					mono_field_set_value(event_object, event_key_mod_field, (void*)&e.key_mod);

					// Finally execute the callback callee
					MonoMethod* callback_mtd = mono_class_get_method_from_name(
						callback_class, 
						lumina_csharp_namespace::keyboard_event_callback_type::methods::DISPATCH_MTD,
						0
					);

					MonoObject* exception = nullptr;
					mono_runtime_invoke(callback_mtd, callback, nullptr, &exception);
				}
			);
		}

		// *MouseEventCallback Class*
		if (callback_class_name == lumina_csharp_namespace::mouse_event_callback_type::TYPE_NAME)
		{
			event_listener::get_singleton().submit_event_callback(
				[=](const mouse_event_t& e) -> void
				{
					// Get the keyboard event callback event holder
					MonoClassField* event_field = mono_class_get_field_from_name(
						callback_class,
						lumina_csharp_namespace::mouse_event_callback_type::fields::_EVENT
					);

					// Get's the event object
					MonoObject* event_object;
					mono_field_get_value(callback, event_field, &event_object);
					MonoClass* event_object_class = mono_object_get_class(event_object);

					MonoClassField* event_type_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::event_base_type::fields::_EVENT_TYPE
					);

					MonoClassField* event_action_type_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_ACTION_TYPE
					);

					MonoClassField* event_mouse_event_type_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_MOUSE_EVENT_TYPE
					);

					MonoClassField* event_button_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_BUTTON
					);

					MonoClassField* event_cursor_pos_x_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_CURSOR_POS_X
					);

					MonoClassField* event_cursor_pox_y_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_CURSOR_POS_Y
					);

					MonoClassField* event_mouse_wheel_x_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_MOUSE_WHEEL_X
					);

					MonoClassField* event_mouse_wheel_y_field = mono_class_get_field_from_name(
						event_object_class,
						lumina_csharp_namespace::mouse_event_type::fields::_MOUSE_WHEEL_Y
					);
					
					// Set the values for the current event happened in the event object
					mono_field_set_value(event_object, event_type_field, (void*)&e.event_type);
					mono_field_set_value(event_object, event_action_type_field, (void*)&e.action_type);
					mono_field_set_value(event_object, event_mouse_event_type_field, (void*)&e.mouse_event_subtype);
					mono_field_set_value(event_object, event_button_field, (void*)&e.mouse_button);
					mono_field_set_value(event_object, event_cursor_pos_x_field, (void*)&e.cursor_pos_x);
					mono_field_set_value(event_object, event_cursor_pox_y_field, (void*)&e.cursor_pos_y);
					mono_field_set_value(event_object, event_mouse_wheel_x_field, (void*)&e.mouse_wheel_x);
					mono_field_set_value(event_object, event_mouse_wheel_y_field, (void*)&e.mouse_wheel_y);

					// Finally execute the callback callee
					MonoMethod* callback_mtd = mono_class_get_method_from_name(
						callback_class,
						lumina_csharp_namespace::mouse_event_callback_type::methods::DISPATCH_MTD,
						0
					);

					MonoObject* exception = nullptr;
					mono_runtime_invoke(callback_mtd, callback, nullptr, &exception);
				}
			);
		}
	}

	void script_binder::bind_event_handler(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::event_handler_csharp_type::methods::IS_KEY_PRESSED,
			lumina_csharp_namespace::event_handler_csharp_type::TYPE_NAME,
			event_handler_is_key_pressed_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::event_handler_csharp_type::methods::IS_KEY_RELEASED,
			lumina_csharp_namespace::event_handler_csharp_type::TYPE_NAME,
			event_handler_is_key_released_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::event_handler_csharp_type::methods::IS_KEY_HELD,
			lumina_csharp_namespace::event_handler_csharp_type::TYPE_NAME,
			event_handler_is_key_held_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::event_handler_csharp_type::methods::REGISTER_EVENT_CALLBACK,
			lumina_csharp_namespace::event_handler_csharp_type::TYPE_NAME,
			event_handler_register_event_callback_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion

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
		MonoClassField* scene_name_field = mono_class_get_field_from_name(
			scene_class,
			lumina_csharp_namespace::scene_csharp_type::fields::_NAME
		);

		// Assign the Scene Name
		MonoString* scene_name_value = core_script_ref->create_mono_str(scene_res->get_name());
		mono_field_set_value(*scene_out, scene_name_field, scene_name_value);

		return true;
	}

	static bool scene_manager_switch_scene_func(MonoString* scene_name)
	{
		// Switch the scene
		scenes_system::get_singleton().activate_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);

		return true;
	}

	static bool scene_manager_destroy_scene_func(MonoString* scene_name)
	{
		// Destroy the scene
		return scenes_system::get_singleton().destroy_scene(
			mono_type_utils::mono_str_to_utf8_str(scene_name)
		);
	}

	static void scene_manager_destroy_all_func()
	{
		// Destroy all the scenes
		scenes_system::get_singleton().destroy_all();
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

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_manager_csharp_type::methods::SWITCH_SCENE,
			lumina_csharp_namespace::scene_manager_csharp_type::TYPE_NAME,
			scene_manager_switch_scene_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_manager_csharp_type::methods::DESTROY_SCENE,
			lumina_csharp_namespace::scene_manager_csharp_type::TYPE_NAME,
			scene_manager_destroy_scene_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::scene_manager_csharp_type::methods::DESTROY_ALL,
			lumina_csharp_namespace::scene_manager_csharp_type::TYPE_NAME,
			scene_manager_destroy_all_func,
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

	template<typename component_type>
	static void init_component_class_from_internal_component(MonoObject* obj, MonoClass* obj_class, entity entity_req);

	template<>
	static void init_component_class_from_internal_component<identity_component>(MonoObject* obj, MonoClass* obj_class, entity entity_req)
	{
		// Get entity out fields and properties to assign
		MonoClassField* component_id_field = mono_class_get_field_from_name(
			obj_class,
			lumina_csharp_namespace::identifier_csharp_type::fields::_ID
		);

		MonoClassField* component_name_field = mono_class_get_field_from_name(
			obj_class,
			lumina_csharp_namespace::identifier_csharp_type::fields::_NAME
		);

		identity_component& identifier = entity_req.get_component<identity_component>();

		// Assign the Component Id
		MonoString* component_id_value = core_script_ref->create_mono_str(identifier.id);
		mono_field_set_value(obj, component_id_field, component_id_value);

		// Assign the Component Name
		MonoString* component_name_value = core_script_ref->create_mono_str(identifier.name);
		mono_field_set_value(obj, component_name_field, component_name_value);
	}

	template<>
	static void init_component_class_from_internal_component<transform_component>(MonoObject* obj, MonoClass* obj_class, entity entity_req)
	{
		// Nothing to implement here for now
	}

	template<>
	static void init_component_class_from_internal_component<sprite_component>(MonoObject* obj, MonoClass* obj_class, entity entity_req)
	{
		// Nothing to implement here for now
	}

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
			init_component_class_from_internal_component<identity_component>(component_out_ref, component_class, entity_req);

		// *Transform Class*
		if (component_class_name == lumina_csharp_namespace::transform_csharp_type::TYPE_NAME)
			init_component_class_from_internal_component<transform_component>(component_out_ref, component_class, entity_req);

		// *Sprite Class*
		if (component_class_name == lumina_csharp_namespace::sprite_csharp_type::TYPE_NAME)
			init_component_class_from_internal_component<sprite_component>(component_out_ref, component_class, entity_req);

		return true;
	}

	static bool entity_add_component_func(entt::entity entity_id, entt::registry* entity_reg_ptr, MonoObject** component_out)
	{
		MonoObject* component_out_ref = *component_out;

		if (entity_reg_ptr == nullptr)
			return false;

		// Construct the requested entity
		entity entity_req = entity(entity_reg_ptr, entity_id);

		// Get the component class
		MonoClass* component_class = mono_object_get_class(component_out_ref);
		std::string component_class_name = mono_class_get_name(component_class);

		// *Transform Class*
		if (component_class_name == lumina_csharp_namespace::transform_csharp_type::TYPE_NAME)
		{
			if(!entity_req.has_component<transform_component>())
				entity_req.add_component<transform_component>();

			init_component_class_from_internal_component<transform_component>(component_out_ref, component_class, entity_req);
		}

		// *Sprite Class*
		if (component_class_name == lumina_csharp_namespace::sprite_csharp_type::TYPE_NAME)
		{
			if (!entity_req.has_component<sprite_component>())
				entity_req.add_component<sprite_component>();

			init_component_class_from_internal_component<sprite_component>(component_out_ref, component_class, entity_req);
		}

		return true;
	}

	static bool entity_has_component_func(entt::entity entity_id, entt::registry* entity_reg_ptr, MonoObject* component_out)
	{
		if (entity_reg_ptr == nullptr)
			return false;

		// Construct the requested entity
		entity entity_req = entity(entity_reg_ptr, entity_id);

		// Get the component class
		MonoClass* component_class = mono_object_get_class(component_out);
		std::string component_class_name = mono_class_get_name(component_class);

		// *Identifier Class*
		if (component_class_name == lumina_csharp_namespace::identifier_csharp_type::TYPE_NAME)
			return entity_req.has_component<identity_component>();

		// *Transform Class*
		if (component_class_name == lumina_csharp_namespace::transform_csharp_type::TYPE_NAME)
			return entity_req.has_component<transform_component>();

		// *Sprite Class*
		if (component_class_name == lumina_csharp_namespace::sprite_csharp_type::TYPE_NAME)
			return entity_req.has_component<sprite_component>();

		return false;
	}

	void script_binder::bind_entity(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::entity_csharp_type::methods::GET_COMPONENT,
			lumina_csharp_namespace::entity_csharp_type::TYPE_NAME,
			entity_get_component_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::entity_csharp_type::methods::ADD_COMPONENT,
			lumina_csharp_namespace::entity_csharp_type::TYPE_NAME,
			entity_add_component_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::entity_csharp_type::methods::HAS_COMPONENT,
			lumina_csharp_namespace::entity_csharp_type::TYPE_NAME,
			entity_has_component_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion

#pragma region Vectors

	static void set_vec3_xyz_fields(MonoObject* vectorInstance, l_float32 x, l_float32 y, l_float32 z)
	{
		MonoClass* vec_out_class = mono_object_get_class(vectorInstance);
		MonoClassField* vec_out_x_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_X
		);

		MonoClassField* vec_out_y_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Y
		);

		MonoClassField* vec_out_z_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Z
		);

		mono_field_set_value(vectorInstance, vec_out_x_field, &x);
		mono_field_set_value(vectorInstance, vec_out_y_field, &y);
		mono_field_set_value(vectorInstance, vec_out_z_field, &z);
	}

	static void set_vec4_xyzw_fields(MonoObject* vectorInstance, l_float32 x, l_float32 y, l_float32 z, l_float32 w)
	{
		MonoClass* vec_out_class = mono_object_get_class(vectorInstance);
		MonoClassField* vec_out_x_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec4_csharp_type::fields::_X
		);

		MonoClassField* vec_out_y_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec4_csharp_type::fields::_Y
		);

		MonoClassField* vec_out_z_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec4_csharp_type::fields::_Z
		);

		MonoClassField* vec_out_w_field = mono_class_get_field_from_name(
			vec_out_class,
			lumina_csharp_namespace::vec4_csharp_type::fields::_W
		);

		mono_field_set_value(vectorInstance, vec_out_x_field, &x);
		mono_field_set_value(vectorInstance, vec_out_y_field, &y);
		mono_field_set_value(vectorInstance, vec_out_z_field, &z);
		mono_field_set_value(vectorInstance, vec_out_w_field, &w);
	}

#pragma endregion

#pragma region Transform

	static entity fetch_entity_from_mono_obj(MonoObject* ownerEntity)
	{

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_FAST

		// Check if the entity is valid and has a transform attached
		if (ownerEntity == nullptr)
			return entity();

#endif 

		// Get's the entity id and reg ptr
		MonoClass* owner_entity_class = mono_object_get_class(ownerEntity);

		return {
			core_script_ref->get_field_value<entt::registry*>(
				ownerEntity,
				owner_entity_class,
				lumina_csharp_namespace::entity_csharp_type::fields::_REGISTRY_PTR
			),
			core_script_ref->get_field_value<entt::entity>(
				ownerEntity,
				owner_entity_class,
				lumina_csharp_namespace::entity_csharp_type::fields::_ID
			)
		};
	}

	static void transform_get_position_func(MonoObject* ownerEntity, MonoObject** vecOut)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<transform_component>())
			return;

#endif 

		// Set the value of the out vector
		glm::vec3 position = entity_fetched.get_component<transform_component>().get_position();

		set_vec3_xyz_fields(*vecOut, position.x, position.y, position.z);
	}

	static void transform_get_euler_angles_rotation_func(MonoObject* ownerEntity, MonoObject** vecOut)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<transform_component>())
			return;

#endif 

		// Set the value of the out vector
		glm::vec3 euler_angles_rot = entity_fetched.get_component<transform_component>().get_euler_angles();

		set_vec3_xyz_fields(*vecOut, euler_angles_rot.x, euler_angles_rot.y, euler_angles_rot.z);
	}

	static void transform_get_scale_func(MonoObject* ownerEntity, MonoObject** vecOut)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<transform_component>())
			return;

#endif 

		// Set the value of the out vector
		glm::vec3 scale = entity_fetched.get_component<transform_component>().get_scale();

		set_vec3_xyz_fields(*vecOut, scale.x, scale.y, scale.z);
	}

	static void transform_set_position_func(MonoObject* ownerEntity, MonoObject* vecToSet)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<transform_component>())
			return;

#endif 

		transform_component& entity_transform = entity_fetched.get_component<transform_component>();
		entity_hierarchy_component& entity_hierarchy = entity_fetched.get_component<entity_hierarchy_component>();
		glm::mat4 pre_transformation_matrix = entity_transform.get_model_matrix();

		// Get's the vector x,y,z 
		MonoClass* vec_class = mono_object_get_class(vecToSet);

		l_float32 x = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_X
		);

		l_float32 y = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Y
		);

		l_float32 z = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Z
		);

		// Set the value of the out vector
		entity_transform.set_position({ x , y , z });

		// If the entity has childs apply the position to all the childs
		if (entity_hierarchy.has_childs())
		{
			entity_hierarchy.dispatch_func_to_childs(
				[&](lumina::entity& ent_iterated) -> void
				{
					if (!ent_iterated.has_component<lumina::transform_component>())
						return;

					lumina::transform_component& ent_ith_transform = ent_iterated.get_component<lumina::transform_component>();
					ent_ith_transform.set_model(
						lumina::transform_component::compute_models_difference(pre_transformation_matrix, entity_transform.get_model_matrix()) *
						ent_ith_transform.get_model_matrix()
					);
				}
			);
		}
	}

	static void transform_rotate_func(MonoObject* ownerEntity, MonoObject* vecToSet, float angleDeg)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<transform_component>())
			return;

#endif 

		transform_component& entity_transform = entity_fetched.get_component<transform_component>();
		entity_hierarchy_component& entity_hierarchy = entity_fetched.get_component<entity_hierarchy_component>();
		glm::mat4 pre_transformation_matrix = entity_transform.get_model_matrix();

		// Get's the vector x,y,z 
		MonoClass* vec_class = mono_object_get_class(vecToSet);

		l_float32 x = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_X
		);

		l_float32 y = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Y
		);

		l_float32 z = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Z
		);

		// Set the value of the out vector
		entity_transform.rotate({ x , y , z }, glm::radians(angleDeg));

		// If the entity has childs apply the position to all the childs
		if (entity_hierarchy.has_childs())
		{
			entity_hierarchy.dispatch_func_to_childs(
				[&](lumina::entity& ent_iterated) -> void
				{
					if (!ent_iterated.has_component<lumina::transform_component>())
						return;

					lumina::transform_component& ent_ith_transform = ent_iterated.get_component<lumina::transform_component>();
					ent_ith_transform.set_model(
						lumina::transform_component::compute_models_difference(pre_transformation_matrix, entity_transform.get_model_matrix()) *
						ent_ith_transform.get_model_matrix()
					);
				}
			);
		}
	}

	static void transform_set_scale_func(MonoObject* ownerEntity, MonoObject* vecToSet)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<transform_component>())
			return;

#endif 

		transform_component& entity_transform = entity_fetched.get_component<transform_component>();
		entity_hierarchy_component& entity_hierarchy = entity_fetched.get_component<entity_hierarchy_component>();
		glm::mat4 pre_transformation_matrix = entity_transform.get_model_matrix();

		// Get's the vector x,y,z 
		MonoClass* vec_class = mono_object_get_class(vecToSet);

		l_float32 x = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_X
		);

		l_float32 y = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Y
		);

		l_float32 z = core_script_ref->get_field_value<l_float32>(
			vecToSet,
			vec_class,
			lumina_csharp_namespace::vec3_csharp_type::fields::_Z
		);

		// Set the value of the out vector
		entity_transform.set_scale({ x , y , z });

		// If the entity has childs apply the position to all the childs
		if (entity_hierarchy.has_childs())
		{
			entity_hierarchy.dispatch_func_to_childs(
				[&](lumina::entity& ent_iterated) -> void
				{
					if (!ent_iterated.has_component<lumina::transform_component>())
						return;

					lumina::transform_component& ent_ith_transform = ent_iterated.get_component<lumina::transform_component>();
					ent_ith_transform.set_model(
						lumina::transform_component::compute_models_difference(pre_transformation_matrix, entity_transform.get_model_matrix()) *
						ent_ith_transform.get_model_matrix()
					);
				}
			);
		}
	}

	void script_binder::bind_transform(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::transform_csharp_type::methods::GET_POSITION,
			lumina_csharp_namespace::transform_csharp_type::TYPE_NAME,
			transform_get_position_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::transform_csharp_type::methods::GET_EULER_ANGLES_ROTATION,
			lumina_csharp_namespace::transform_csharp_type::TYPE_NAME,
			transform_get_euler_angles_rotation_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::transform_csharp_type::methods::GET_SCALE,
			lumina_csharp_namespace::transform_csharp_type::TYPE_NAME,
			transform_get_scale_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::transform_csharp_type::methods::SET_POSITION,
			lumina_csharp_namespace::transform_csharp_type::TYPE_NAME,
			transform_set_position_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::transform_csharp_type::methods::ROTATE,
			lumina_csharp_namespace::transform_csharp_type::TYPE_NAME,
			transform_rotate_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);

		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::transform_csharp_type::methods::SET_SCALE,
			lumina_csharp_namespace::transform_csharp_type::TYPE_NAME,
			transform_set_scale_func,
			lumina_csharp_namespace::NAMESPACE_NAME
		);
	}

#pragma endregion

#pragma region Sprite

	static void sprite_get_color_func(MonoObject* ownerEntity, MonoObject** vecOut)
	{
		entity entity_fetched = fetch_entity_from_mono_obj(ownerEntity);

#if LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_LEVELS >= LUMINA_INTERNAL_CALLS_SECURITY_CHECKS_MAX

		// Check if the entity has the trasnform component attached, this is supposed to be always true for the code flow safety
		// but a security check is added as a plus.
		if (!entity_fetched.has_component<sprite_component>())
			return;

#endif 

		set_vec4_xyzw_fields(
			*vecOut, 
			entity_fetched.get_component<sprite_component>().color.x, 
			entity_fetched.get_component<sprite_component>().color.y, 
			entity_fetched.get_component<sprite_component>().color.z,
			entity_fetched.get_component<sprite_component>().color.w
		);
	}

	void script_binder::bind_sprite(mono_script* script_to_forward_binds)
	{
		cs_t_ref_eval::mtd_internal_call(
			lumina_csharp_namespace::sprite_csharp_type::methods::GET_COLOR,
			lumina_csharp_namespace::sprite_csharp_type::TYPE_NAME,
			sprite_get_color_func,
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