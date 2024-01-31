#pragma once

#include "d3d11_instance.h"

#include <vector>

namespace lumina
{
	class d3d11_index_buffer
	{
	public:

		// Allocate the index buffer with a given size
		bool allocate(uint32_t size);

		// Add indicies in the index buffer
		void push_indicies(const std::vector<uint32_t>& indicies);

		// Remove the last element in the index buffer
		void pop_index();

		// Enable the index buffer for the current render pass
		void enable() const;

		// Wheter if the index buffer is allocated or not
		const bool is_allocated() const { return index_buffer_ != nullptr; }

		// Return the holded indicies data (array of uint32_t indicies)
		const std::vector<uint32_t>& get_indicies_data() const { return indicies_array_data_; }

	private:

		ID3D11Buffer* index_buffer_ = nullptr;
		std::vector<uint32_t> indicies_array_data_;

		void load_data(const void* data, uint32_t size) const;

	};

}