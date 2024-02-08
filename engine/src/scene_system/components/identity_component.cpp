#include "identity_component.h"

namespace lumina
{
	identity_component::identity_component()
	{
		id = lumina_strings_s::generate_uuidv4();
		name = "Empty Object";
	}
}