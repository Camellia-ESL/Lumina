#include "asset.h"

#include "graphics/texture.h"
#include "core/lumina_strings.h"

namespace lumina
{
	asset::asset()
	{
		id_ = lumina_strings_s::generate_uuidv4();
		name_ = "New Asset";
	}

	asset::~asset()
	{
		if (resource_type_ == resource_types_e::TEXTURE)
			delete reinterpret_cast<texture*>(holded_resource_);
	}
}