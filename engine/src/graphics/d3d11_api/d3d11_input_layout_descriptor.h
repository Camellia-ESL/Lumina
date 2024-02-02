#pragma once

#include "d3d11_shader.h"

#include <d3d11.h>
#include <vector>

namespace lumina
{
	class d3d11_input_layout_descriptor
	{
	public:

		~d3d11_input_layout_descriptor() { destroy(); }

		// Allocates a new descriptor
		bool allocate(d3d11_shader* shader, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptor);

		// Free the resources
		void destroy() { input_layout_->Release(); }

		// Wheter if the descriptor holded by the class instance exist or not
		const bool is_allocated() const { return input_layout_ != nullptr; }

		// Enable the descriptor for the current render pass
		void enable() const;

	private:

		ID3D11InputLayout* input_layout_ = nullptr;
		std::vector<D3D11_INPUT_ELEMENT_DESC> input_elements_descriptor_;

	};
}