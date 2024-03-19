#pragma once

#include <d3d11.h>

namespace lumina
{
	class d3d11_depth_stencil
	{
	public:

		// Allocate a depth stencil buffer
		bool allocate();

		// Enable the stencil for the current render pass
		void enable() const;

		// Clear the depth buffer (clear color vec4 float)
		void clear_buffer(float* clear_color) const;

		// Wheter if the depth stencil is allocated or not
		const bool is_allocated() const { return depth_stencil_view_ != nullptr; }

		// Destroy the depth stencil
		void destroy() { if (is_allocated()) { depth_stencil_state_->Release(); depth_stencil_view_->Release(); depth_stencil_state_ = nullptr; depth_stencil_view_ = nullptr; } }

	private:

		ID3D11DepthStencilView* depth_stencil_view_ = nullptr;
		ID3D11DepthStencilState* depth_stencil_state_ = nullptr;

	};
}