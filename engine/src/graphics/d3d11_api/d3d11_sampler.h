#pragma once

#include "d3d11.h"

namespace lumina
{
	class d3d11_sampler
	{
	public:

		// Allocate a default sampler
		bool allocate();

		// Allocate a sampler with a given sampler descriptor
		bool allocate(const D3D11_SAMPLER_DESC& sampler_descriptor);

		// Wheter if the sampler is allocated or not
		const bool is_allocated() const { return d3d_sampler_state_ != nullptr; }

		// Enables the sampler for the current render pass
		void enable() const;

	private:

		ID3D11SamplerState* d3d_sampler_state_ = nullptr;

	};
}