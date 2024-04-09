#include "d3d11_depth_stencil.h"

#include "d3d11_instance.h"
#include "application/app.h"

#include "spdlog/spdlog.h"

namespace lumina
{
	bool d3d11_depth_stencil::allocate()
	{
		const glm::vec2 surface_dim = application_player::get_singleton().get_surface().get_dimensions();

		if (surface_dim.x == 0.0f || surface_dim.y == 0.0f)
			return false;

		// Create's depth stencil view
		D3D11_TEXTURE2D_DESC depth_texture_descriptor{};
		depth_texture_descriptor.Width = surface_dim.x;
		depth_texture_descriptor.Height = surface_dim.y;
		depth_texture_descriptor.MipLevels = 1;
		depth_texture_descriptor.ArraySize = 1;
		depth_texture_descriptor.Usage = D3D11_USAGE_DEFAULT;
		depth_texture_descriptor.SampleDesc.Count = 1;
		depth_texture_descriptor.Format = DXGI_FORMAT_R24G8_TYPELESS;
		depth_texture_descriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ID3D11Texture2D* depth_stencil_texture;
		HRESULT result = d3d11_instance::get_singleton().get_device()->CreateTexture2D(
			&depth_texture_descriptor, 
			NULL, 
			&depth_stencil_texture
		);

		if (result != S_OK)
		{
			spdlog::error("D3D11 Depth Stencil -> Error creating the depth stencil view texture 2D.");
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc{};
		depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		result = d3d11_instance::get_singleton().get_device()->CreateDepthStencilView(
			depth_stencil_texture, 
			&depth_stencil_view_desc, 
			&depth_stencil_view_
		);

		depth_stencil_texture->Release();

		// Create's depth stencil state 
		D3D11_DEPTH_STENCIL_DESC depth_state_descriptor{};
		depth_state_descriptor.DepthEnable = true; // Here the value should be changed with a variable to handle depth activation or deactivation before starting the engine
		depth_state_descriptor.DepthFunc = D3D11_COMPARISON_LESS;
		depth_state_descriptor.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		result = d3d11_instance::get_singleton().get_device()->CreateDepthStencilState(
			&depth_state_descriptor, 
			&depth_stencil_state_
		);

		return result == S_OK;
	}

	void d3d11_depth_stencil::enable() const
	{
		auto* main_render_target_view = d3d11_instance::get_singleton().get_main_render_target_view();
		
		// Enable depth stencil view
		d3d11_instance::get_singleton().get_device_context()->OMSetRenderTargets(
			1,
			&main_render_target_view,
			depth_stencil_view_
		);

		// Enable depth stencil state
		d3d11_instance::get_singleton().get_device_context()->OMSetDepthStencilState(
			depth_stencil_state_, 
			0
		);
	}

	void d3d11_depth_stencil::clear_buffer(float* clear_color) const
	{
		d3d11_instance::get_singleton().get_device_context()->ClearDepthStencilView(
			depth_stencil_view_,
			D3D11_CLEAR_DEPTH,
			1.0f,
			0
		);

		d3d11_instance::get_singleton().get_device_context()->ClearRenderTargetView(
			d3d11_instance::get_singleton().get_main_render_target_view(), 
			clear_color
		);
	}
}