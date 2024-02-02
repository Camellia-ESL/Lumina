#include "d3d11_renderer.h"

#include "d3d11_instance.h"
#include "../d3d11_2d_renderers/d3d11_quad_renderer.h"

#include "spdlog/spdlog.h"

#include <Windows.h>

namespace lumina
{
	d3d11_renderer* d3d11_renderer::instance_ = nullptr;

	void d3d11_renderer::init(HWND window)
	{
        d3d11_instance* instance = new d3d11_instance();

        if (!d3d11_instance::get_singleton().create_device(window))
        {
            spdlog::error("Error creating D3D Device!");
            return;
        }

        // Init shapes batch renderers
        d3d11_quad_renderer_s::init();
	}

    void d3d11_renderer::clear_screen()
    {
        constexpr const float clear_color_with_alpha[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
        ID3D11RenderTargetView* render_target = d3d11_instance::get_singleton().get_main_render_target_view();
        
        d3d11_instance::get_singleton().get_device_context()->OMSetRenderTargets(
            1,
            &render_target,
            nullptr
        );

        d3d11_instance::get_singleton().get_device_context()->ClearRenderTargetView(render_target, clear_color_with_alpha);
    }

    void d3d11_renderer::present()
    {
        d3d11_instance::get_singleton().get_swap_chain()->Present(FALSE, 0);
    }

    void d3d11_renderer::handle_resize(const float width, const float height)
    {
        d3d11_instance::get_singleton().cleanup_render_target();
        d3d11_instance::get_singleton().get_swap_chain()->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
        d3d11_instance::get_singleton().create_render_target();
    }
}