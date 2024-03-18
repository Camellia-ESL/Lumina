#include "d3d11_depth_stencil.h"

#include "d3d11_instance.h"
#include "application/app.h"

namespace lumina
{
	bool d3d11_depth_stencil::allocate()
	{
		const glm::vec2 surface_dim = application_player::get_singleton().get_surface().get_dimensions();

		D3D11_TEXTURE2D_DESC depth_texture_descriptor;
		ZeroMemory(&depth_texture_descriptor, sizeof(depth_texture_descriptor));
		depth_texture_descriptor.Width = surface_dim.x;
		depth_texture_descriptor.Height = surface_dim.y;
		depth_texture_descriptor.MipLevels = 1;
		depth_texture_descriptor.ArraySize = 1;
		depth_texture_descriptor.SampleDesc.Count = 1;
		depth_texture_descriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_texture_descriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ID3D11Texture2D* depth_stencil_texture;
		bool result = d3d11_instance::get_singleton().get_device()->CreateTexture2D(&depth_texture_descriptor, NULL, &depth_stencil_texture);

		if (result != S_OK)
			return false;

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
		ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
		depth_stencil_view_desc.Format = depth_texture_descriptor.Format;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

		result = d3d11_instance::get_singleton().get_device()->CreateDepthStencilView(depth_stencil_texture, &depth_stencil_view_desc, &depth_stencil_);
		depth_stencil_texture->Release();

		return result == S_OK;
	}

	void d3d11_depth_stencil::enable() const
	{
		auto* main_render_target_view = d3d11_instance::get_singleton().get_main_render_target_view();
		d3d11_instance::get_singleton().get_device_context()->OMSetRenderTargets(
			1,
			&main_render_target_view,
			depth_stencil_
		);
	}

	void d3d11_depth_stencil::clear_buffer(float* clear_color) const
	{
		d3d11_instance::get_singleton().get_device_context()->ClearDepthStencilView(
			depth_stencil_,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0
		);

		d3d11_instance::get_singleton().get_device_context()->ClearRenderTargetView(
			d3d11_instance::get_singleton().get_main_render_target_view(), 
			clear_color
		);
	}
}