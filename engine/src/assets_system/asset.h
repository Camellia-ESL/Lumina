#pragma once

#include <string>

namespace lumina
{
	// Represent an asset that holds a resource,
	// asset are unique and distinguished by a UUID created when instanced the object
	class asset
	{
	public:
		
		// The enum that contains all the available resource types
		enum class resource_types_e
		{
			// Represent an asset holding nothing
			NULL_RESOURCE,
			// Represent a texture resource
			TEXTURE
			// **IMPORTANT**: Whenever a new resource type get's added here remember to free the memory on asset deconstruction with the right type
		};

	public:

		asset();
		~asset();

		const std::string& get_asset_id() const { return id_; }
		const std::string& get_asset_name() const { return name_; }
		const resource_types_e get_type() const { return resource_type_; }

		template<typename asset_resource_type_cast>
		asset_resource_type_cast* get_resource() { return reinterpret_cast<asset_resource_type_cast*>(holded_resource_); }
		
		void set_name(const std::string& name) { name_ = name; }
		void set_resource(void* resource_ptr, resource_types_e resource_type) { holded_resource_ = resource_ptr; resource_type_ = resource_type; }

	private:

		std::string id_;
		std::string name_;
		resource_types_e resource_type_ = resource_types_e::NULL_RESOURCE;
		void* holded_resource_;

	};
}