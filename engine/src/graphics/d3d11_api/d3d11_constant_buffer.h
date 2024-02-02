#pragma once

#include "d3d11_instance.h"

#include <cstdint>

namespace lumina
{
	class d3d11_constant_buffer
	{
	public:

		// Allocate the buffer
		bool allocate(uint32_t size);

		// Load data in the constant buffer
		void load_data(const void* data, uint32_t size) const;

		// Enable the constant buffer for the current render pass
		void enable(uint32_t slot = 0) const;

		const bool is_allocated() const { return constant_buffer_ != nullptr; }

	private:

		ID3D11Buffer* constant_buffer_ = nullptr;

	};
}