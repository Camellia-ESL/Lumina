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

		struct scene_manager_csharp_type
		{
			static constexpr const char* TYPE_NAME = "SceneManager";

			struct methods
			{
				// private static extern bool CreateSceneImpl(string name);
				static constexpr const char* CREATE_SCENE = "CreateSceneImpl";

				// private static extern Scene GetSceneImpl(string name, ref Scene sceneOut);
				static constexpr const char* GET_SCENE = "GetSceneImpl";
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
		};

		struct entity_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Entity";

			struct methods
			{
				// private static extern bool GetComponentImpl(uint entityId, ulong entityRegPtr, ref object componentOut);
				static constexpr const char* GET_COMPONENT = "GetComponentImpl";
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
			};
		};

		struct transform_csharp_type
		{
			static constexpr const char* TYPE_NAME = "Transform";

			struct methods
			{	
			};

			struct properties
			{
			};

			struct fields
			{	
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