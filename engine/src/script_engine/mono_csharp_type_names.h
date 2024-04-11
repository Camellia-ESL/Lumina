#pragma once
/*
* This header contains all the definitions of the various script API in other languages
* 
* Lumina Engine made by https://github.com/VanityEmptiness/	
*/

#include <string>

namespace lumina
{
	struct lumina_csharp_namespace
	{
		static constexpr const char* NAMESPACE_NAME = "Lumina";

		struct application_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Application";

			struct methods
			{
				// private static extern float GetDeltaTimeImpl();
				static constexpr const char* GET_DELTA_TIME = "GetDeltaTimeImpl";
			};
		};

		struct event_handler_csharp_type
		{
			static constexpr const char* TYPE_NAME = "EventHandler";

			struct methods
			{
				// private static extern bool IsKeyPressedImpl(KeyboardKeyType key);
				static constexpr const char* IS_KEY_PRESSED = "IsKeyPressedImpl";
				// private static extern bool IsKeyReleasedImpl(KeyboardKeyType key);
				static constexpr const char* IS_KEY_RELEASED = "IsKeyReleasedImpl";
				// private static extern bool IsKeyHeldImpl(KeyboardKeyType key);
				static constexpr const char* IS_KEY_HELD = "IsKeyHeldImpl";
			};
		};

		struct scene_manager_csharp_type
		{
			static constexpr const char* TYPE_NAME = "SceneManager";

			struct methods
			{
				// private static extern bool CreateSceneImpl(string name);
				static constexpr const char* CREATE_SCENE = "CreateSceneImpl";

				// private static extern Scene GetSceneImpl(string name, ref Scene sceneOut);
				static constexpr const char* GET_SCENE = "GetSceneImpl";

				// private static extern bool SwitchSceneImpl(string name);
				static constexpr const char* SWITCH_SCENE = "SwitchSceneImpl";

				// private static extern bool DestroySceneImpl(string name);
				static constexpr const char* DESTROY_SCENE = "DestroySceneImpl";

				// private static extern bool DestroyAllImpl();
				static constexpr const char* DESTROY_ALL = "DestroyAllImpl";

			};
		};

		struct scene_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Scene";

			struct methods
			{
				// private static extern bool CreateEntityImpl(string sceneName, ref Entity entityOut);
				static constexpr const char* CREATE_ENTITY = "CreateEntityImpl";
				// private static extern bool GetEntityByNameImpl(string sceneName, string entityName, ref Entity entityOut);
				static constexpr const char* GET_ENTITY_BY_NAME = "GetEntityByNameImpl";
				// private static extern void DestroyEntityImpl(string sceneName, Entity entity);
				static constexpr const char* DESTROY_ENTITY = "DestroyEntityImpl";
			};

			struct properties
			{
				static constexpr const char* NAME = "Name";
			};

			struct fields
			{
				static constexpr const char* _NAME = "_name";
			};
		};

		struct entity_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Entity";

			struct methods
			{
				// private static extern bool GetComponentImpl(uint entityId, ulong entityRegPtr, ref object componentOut);
				static constexpr const char* GET_COMPONENT = "GetComponentImpl";
				// private static extern bool AddComponentImpl(uint entityId, ulong entityRegPtr, ref object componentOut);
				static constexpr const char* ADD_COMPONENT = "AddComponentImpl";
				// private static extern bool HasComponentImpl(uint entityId, ulong entityRegPtr, object componentOut);
				static constexpr const char* HAS_COMPONENT = "HasComponentImpl";
			};

			struct properties
			{
				static constexpr const char* ID = "Id";
			};

			struct fields
			{
				static constexpr const char* _REGISTRY_PTR = "_registryPtr";
				static constexpr const char* _ID = "_id";
			};
		};

		struct component_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Component";

			struct methods
			{
			};

			struct properties
			{
				static constexpr const char* OWNER_ENTITY = "OwnerEntity";
			};

			struct fields
			{
				static constexpr const char* _OWNER_ENTITY = "_ownerEntity";
			};
		};

		struct identifier_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Identifier";

			struct methods
			{
			};

			struct properties
			{
				static constexpr const char* ID = "Id";
				static constexpr const char* NAME = "Name";
			};

			struct fields
			{
				static constexpr const char* _ID = "_id";
				static constexpr const char* _NAME = "_name";
			};
		};

		struct transform_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Transform";

			struct methods
			{	
				// private static extern void GetPositionImpl(Entity ownerEntity, ref Vec3 outVec);
				static constexpr const char* GET_POSITION = "GetPositionImpl";
				// private static extern void GetEulerAnglesRotationImpl(Entity ownerEntity, ref Vec3 outVec);
				static constexpr const char* GET_EULER_ANGLES_ROTATION = "GetEulerAnglesRotationImpl";
				// private static extern void GetScaleImpl(Entity ownerEntity, ref Vec3 outVec);
				static constexpr const char* GET_SCALE = "GetScaleImpl";
				// private static extern void SetPositionImpl(Entity ownerEntity, Vec3 outVec);
				static constexpr const char* SET_POSITION = "SetPositionImpl";
				// private static extern void RotateImpl(Entity ownerEntity, Vec3 outVec, float angle);
				static constexpr const char* ROTATE = "RotateImpl";
				// private static extern void SetScaleImpl(Entity ownerEntity, Vec3 outVec);
				static constexpr const char* SET_SCALE = "SetScaleImpl";
			};

			struct properties
			{
				static constexpr const char* POSITION = "Position";
				static constexpr const char* ROTATION = "Rotation";
				static constexpr const char* SCALE = "Scale";
			};

			struct fields
			{	
			};
		};

		struct sprite_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Sprite";

			struct methods
			{
				// private static extern void GetColorImpl(Entity ownerEntity, ref Vec4 outVec);
				static constexpr const char* GET_COLOR = "GetColorImpl";
			};

			struct properties
			{
			};

			struct fields
			{
			};
		};

		struct vec2_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Vec2";

			struct methods
			{
			};

			struct properties
			{
				static constexpr const char* X = "X";
				static constexpr const char* Y = "Y";
			};

			struct fields
			{
				static constexpr const char* _X = "_x";
				static constexpr const char* _Y = "_y";
			};
		};

		struct vec3_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Vec3";

			struct methods
			{
			};

			struct properties
			{
				static constexpr const char* X = "X";
				static constexpr const char* Y = "Y";
				static constexpr const char* Z = "Z";
			};

			struct fields
			{
				static constexpr const char* _X = "_x";
				static constexpr const char* _Y = "_y";
				static constexpr const char* _Z = "_z";
			};
		};

		struct vec4_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Vec4";

			struct methods
			{
			};

			struct properties
			{
				static constexpr const char* X = "X";
				static constexpr const char* Y = "Y";
				static constexpr const char* Z = "Z";
				static constexpr const char* W = "W";
			};

			struct fields
			{
				static constexpr const char* _X = "_x";
				static constexpr const char* _Y = "_y";
				static constexpr const char* _Z = "_z";
				static constexpr const char* _W = "_w";
			};
		};

		struct logger_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Logger";

			struct methods
			{
				// public static extern void LogInfo(string msg);
				static constexpr const char* LOG_INFO = "LogInfo";

				// public static extern void LogWarning(string msg);
				static constexpr const char* LOG_WARNING = "LogWarning";

				// public static extern void LogError(string msg);
				static constexpr const char* LOG_ERROR = "LogError";
			};
		};
	};

	// csharp_type_reference_evaluator is a helper class to automatically evaluate c# bindings class names and method names and bind methods 
	struct cs_t_ref_eval
	{
		// Eval a class method (given the class name and class method return the full path)
		static void mtd_internal_call(
			const std::string& method_name, 
			const std::string& class_name, 
			const void* func_to_bind, 
			const std::string& namespace_name = ""
		)
		{
			std::string mtd_str_path = "";

			if (method_name.empty() || class_name.empty())
				return;

			if (!namespace_name.empty())
				mtd_str_path += namespace_name + ".";

			mono_add_internal_call(
				(mtd_str_path + class_name + "::" + method_name).c_str(),
				func_to_bind
			);
		}
	};
}