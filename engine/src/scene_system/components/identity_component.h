#pragma once

#include "component.h"

#include "core/lumina_strings.h"

#include <string>

namespace lumina
{
	// This component is used to identify all the entity and it's consider a based component
	// stands inside of every entity created and should never be deleted.
	struct identity_component : public component
	{
		identity_component();

		// The unique id of the entity
		std::string id;

		// The name of the entity
		std::string name;
	};
}