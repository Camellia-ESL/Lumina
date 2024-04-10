#pragma once

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"

#include <string>

namespace lumina
{
	// Represent's an abstraction of a loaded MonoAssembly
	class mono_script
	{
	public:

		// Loads the assembly from file (must be a mono assembly dll/exe)
		MonoAssembly* load_from_file(const std::string& file_path);

		// Wheter if the mono script object is holding a loaded script or not
		const bool is_loaded() const { return assembly_ptr_ != nullptr; }

		// Get's the definition of a class
		MonoClass* get_class(const std::string& class_name, const std::string& class_namespace = "");

		// Create's a class instance (object) given a class name, by default the namespace is set as global
		MonoObject* create_class_obj(const std::string& class_name, const std::string& class_namespace = "");
		MonoObject* create_class_obj(MonoClass* class_def);
		MonoString* create_mono_str(const char* str);
		MonoString* create_mono_str(const std::string& str);

		// Get's a field value from a class instance (object) given the field name, obj instance and obj class
		// Note: this method is optimized for retrieving multiple fields because it doesn't search the class def as it is already given
		template<typename ret_value_t>
		ret_value_t get_field_value(MonoObject* obj, MonoClass* obj_class, const char* field_name)
		{
			// Get's the field
			MonoClassField* class_field = mono_class_get_field_from_name(
				obj_class,
				field_name
			);

			// Instance a buffer to hold the value to return and fetch the value
			ret_value_t ret_value_buf{};
			mono_field_get_value(obj, class_field, &ret_value_buf);

			return ret_value_buf;
		}

		// Get's a field value from a class instance (object) given the field name and obj instance
		template<typename ret_value_t>
		ret_value_t get_field_value(MonoObject* obj, const char* field_name)
		{
			// Get's the class
			MonoClass* instance_class = mono_object_get_class(obj);

			return get_field_value<ret_value_t>(obj, instance_class, field_name);
		}

	private:
		
		MonoAssembly* assembly_ptr_;

	};
}