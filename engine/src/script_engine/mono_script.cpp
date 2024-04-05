#include "mono_script.h"

#include "core/lumina_file_system.h"

#include "script_engine/script_engine.h"

namespace lumina
{
    MonoAssembly* mono_script::load_from_file(const std::string& file_path)
    {
        l_uint32 file_size = 0;
        char* file_data = (char*)lumina_file_system_s::read_file(file_path, &file_size);

        // NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
        MonoImageOpenStatus status;
        MonoImage* image = mono_image_open_from_data_full(file_data, file_size, 1, &status, 0);

        if (status != MONO_IMAGE_OK)
        {
            const char* errorMessage = mono_image_strerror(status);
            // Log some error message using the errorMessage data
            return nullptr;
        }

        assembly_ptr_ = mono_assembly_load_from_full(image, file_path.c_str(), &status, 0);
        mono_image_close(image);

        // Don't forget to free the file data
        delete[] file_data;

        return assembly_ptr_;
    }

    MonoClass* mono_script::get_class(const std::string& class_name, const std::string& class_namespace)
    {
        // Return if it's not loaded
        if (!is_loaded())
            return nullptr;

        // Get the image of the assembly
        MonoImage* image = mono_assembly_get_image(assembly_ptr_);

        // Get the class
        MonoClass* class_def = mono_class_from_name(image, class_namespace.c_str(), class_name.c_str());

        return class_def;
    }

    MonoObject* mono_script::create_class_obj(const std::string& class_name, const std::string& class_namespace)
    {
        // Return if it's not loaded
        if (!is_loaded())
            return nullptr;
            
        // Allocate memory for the class instance
        MonoObject* class_instance = mono_object_new(script_engine::get_singleton().get_app_domain(), get_class(class_name, class_namespace));
        
        // Init the object (run the constructor function)
        mono_runtime_object_init(class_instance);

        return class_instance;
    }

    MonoObject* mono_script::create_class_obj(MonoClass* class_def)
    {
        // Return if it's not loaded
        if (!is_loaded())
            return nullptr;

        // Allocate memory for the class instance
        MonoObject* class_instance = mono_object_new(script_engine::get_singleton().get_app_domain(), class_def);

        // Init the object (run the constructor function)
        mono_runtime_object_init(class_instance);

        return class_instance;
    }

    MonoString* mono_script::create_mono_str(const char* str)
    {
        return mono_string_new(script_engine::get_singleton().get_app_domain(), str);
    }

    MonoString* mono_script::create_mono_str(const std::string& str)
    {
        return create_mono_str(str.c_str());
    }
}