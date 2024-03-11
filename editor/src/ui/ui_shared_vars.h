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
		ui_shared_var_api uint32_t GIZMO_OPERATION_TYPE = 7; // Watch Imguizmo docs, 7 is translate operation by default
	};
}