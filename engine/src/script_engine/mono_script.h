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

	private:
		
		MonoAssembly* assembly_ptr_;

	};
}