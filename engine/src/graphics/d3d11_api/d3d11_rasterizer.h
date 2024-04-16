#pragma once

#include "d3d11.h"

namespace lumina
{
	// Represent's a D3D11 Rasterizer
	class d3d11_rasterizer
	{
	public:

		// Allocate a default rasterizer
		bool allocate();

		// Allocate a rasterizer with a given rasterizer descriptor
		bool allocate(const D3D11_RASTERIZER_DESC& rasterizer_descriptor);

		// Wheter if the rasterizer is allocated or not
		const bool is_allocated() const { return d3d_rasterizer_state_ != nullptr; }

		// Enables the rasterizer for the current render pass
		void enable() const;

		// Destroy's the rasterizer
		void destroy();

	private:

		ID3D11RasterizerState* d3d_rasterizer_state_ = nullptr;

	};
}