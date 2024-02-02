#include "d3d11_blend_state.h"

namespace lumina
{
	bool d3d11_blend_state::allocate(D3D11_BLEND_DESC* blend_descriptor)
	{
		if (blend_descriptor != nullptr)
		{
			d3d11_instance::get_singleton().get_device()->CreateBlendState(blend_descriptor, &blend_state_);
		}
		else
		{
			// Default blend state allocator
			D3D11_BLEND_DESC blend_state_description;
			ZeroMemory(&blend_state_description, sizeof(D3D11_BLEND_DESC));

			blend_state_description.RenderTarget[0].BlendEnable = TRUE;
			blend_state_description.RenderTarget[0].RenderTargetWriteMask = 0x0f;

			blend_state_description.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blend_state_description.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blend_state_description.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

			blend_state_description.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blend_state_description.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blend_state_description.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

			d3d11_instance::get_singleton().get_device()->CreateBlendState(&blend_state_description, &blend_state_);
		}

		return is_allocated();
	}

	void d3d11_blend_state::enable() const
	{
		d3d11_instance::get_singleton().get_device_context()->OMSetBlendState(blend_state_, blend_factor_, sample_mask_);
	}
}