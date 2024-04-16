#include "d3d11_rasterizer.h"

#include "d3d11_api.h"

namespace lumina
{
	bool d3d11_rasterizer::allocate()
	{
		// Create a rasterizer state description
		D3D11_RASTERIZER_DESC rasterizer_desc{};
		rasterizer_desc.FillMode = D3D11_FILL_SOLID;
		rasterizer_desc.CullMode = D3D11_CULL_NONE;

		return allocate(rasterizer_desc);
	}

	bool d3d11_rasterizer::allocate(const D3D11_RASTERIZER_DESC& rasterizer_descriptor)
	{
		return d3d11_instance::get_singleton().get_device()->CreateRasterizerState(&rasterizer_descriptor, &d3d_rasterizer_state_) == S_OK;
	}

	void d3d11_rasterizer::enable() const
	{
		d3d11_instance::get_singleton().get_device_context()->RSSetState(d3d_rasterizer_state_);
	}

	void d3d11_rasterizer::destroy()
	{
		if (!is_allocated())
			return;

		d3d_rasterizer_state_->Release();
		d3d_rasterizer_state_ = nullptr;
	}
}