#pragma once
/*
*	This header contains a struct with all the shared variables beetween the various views,
*   accessible from anywhere. Note that here could be missing some variables that are passed 
*   in views constructors for safety purpose.
* 
*	**IMPORTANT**: In this struct are only allowed primitive types or typedefs of primitives
*/

#include <cstdint>

#define ui_shared_var_api inline

namespace lumina_editor
{
	namespace ui_shared_vars
	{
		// Watch Imguizmo docs, 7 is translate operation by default
		ui_shared_var_api uint32_t GIZMO_OPERATION_TYPE = 7; 
		// The drag and drop ID for accepting file load drag and drop
		ui_shared_var_api constexpr const char* FILE_TO_LOAD_DAD_ID = "file_to_load_dad"; 
		// The drag and drop ID for accepting texture drag and drop
		ui_shared_var_api constexpr const char* TEXTURE_DAD_ID = "texture_dad";
	};
}