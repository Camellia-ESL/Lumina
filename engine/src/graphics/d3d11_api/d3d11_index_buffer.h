#pragma once

#include "d3d11_instance.h"

#include <vector>

namespace lumina
{
	class d3d11_index_buffer
	{
	public:

		~d3d11_index_buffer() { destroy(); }

		// Allocate the index buffer with a given size
		bool allocate(const std::vector<uint32_t>& indicies);

		// Free the resources
		void destroy() { index_buffer_->Release(); }

		// Enable the index buffer for the current render pass
		void enable() const;

		// Wheter if the index buffer is allocated or not
		const bool is_allocated() const { return index_buffer_ != nullptr; }

		// Return the holded indicies data (array of uint32_t indicies)
		const std::vector<uint32_t>& get_indicies_data() const { return indicies_array_data_; }

		// The number of indicies
		const uint32_t get_indicies_count() const { return indicies_array_data_.size(); }

		// The index buffer size 
		const uint32_t get_size() const { return index_buffer_size_; }

	private:

		ID3D11Buffer* index_buffer_ = nullptr;
		std::vector<uint32_t> indicies_array_data_;
		uint32_t index_buffer_size_ = 0;

	};

}