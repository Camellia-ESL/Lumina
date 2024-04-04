#pragma once

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"

#include <string>

namespace lumina
{
	class mono_type_utils
	{
	public:

        static bool check_mono_error(MonoError& error)
        {
            bool has_error = !mono_error_ok(&error);
            if (has_error)
            {
                unsigned short error_code = mono_error_get_error_code(&error);
                const char* error_msg = mono_error_get_message(&error);
                // Could add a log here
                mono_error_cleanup(&error);
            }
            return has_error;
        }

        static std::string mono_str_to_utf8_str(MonoString* mono_string)
        {
            if (mono_string == nullptr || mono_string_length(mono_string) == 0)
                return "";

            MonoError error;
            char* utf8 = mono_string_to_utf8_checked(mono_string, &error);
            if (check_mono_error(error))
                return "";
            
            std::string result(utf8);
            mono_free(utf8);

            return result;
        }

	};
}