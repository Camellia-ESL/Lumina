#pragma once

#include "d3d11_instance.h"

#include "glm/glm.hpp"

#include <stdint.h>

namespace lumina
{
	class d3d11_blend_state
	{
	public:

		// Allocate a custom blend state (passing nullptr result in a default allocation)
		bool allocate(D3D11_BLEND_DESC* blend_descriptor);
		
		// Set the blend factor
		void set_blend_factor(const glm::vec4& factor) { memcpy(&blend_factor_[0], &factor.x, sizeof(glm::vec4)); }

		// Set the sample mask
		void set_sample_mask(const uint32_t mask) { sample_mask_ = mask; }

		// Enable the blend state for the current render pass
		void enable() const;

		const bool is_allocated() const { return blend_state_ != nullptr; }

	private:

		ID3D11BlendState* blend_state_;
		float blend_factor_[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		uint32_t sample_mask_ = 0xffffffff;
	};
}