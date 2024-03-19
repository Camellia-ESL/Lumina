#include "d3d11_renderer.h"

#include "application/app.h"

#include "d3d11_instance.h"
#include "../d3d11_2d_renderers/d3d11_quad_renderer.h"

#include "spdlog/spdlog.h"

#include <Windows.h>

lumina::d3d11_renderer* lumina::d3d11_renderer::singleton_instance_ = nullptr;

namespace lumina
{
	void d3d11_renderer::init(HWND window)
	{
        spdlog::warn("Creating a d3d11 instance.");

        d3d11_instance* instance = new d3d11_instance();

        if (!d3d11_instance::get_singleton().create_device(window))
        {
            spdlog::error("Error creating D3D Device!");
            return;
        }

        // Init the depth stencil buffer
        depth_stencil_buffer_.allocate();

        // Init shapes batch renderers
        d3d11_quad_renderer_s::init();

        spdlog::info("D3D11 Renderer initialized.");
	}

    void d3d11_renderer::clear_screen()
    {
        float clear_color_with_alpha[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
        depth_stencil_buffer_.enable();
        depth_stencil_buffer_.clear_buffer(clear_color_with_alpha);
    }

    void d3d11_renderer::present()
    {
        d3d11_instance::get_singleton().get_swap_chain()->Present(
            application_player::get_singleton().get_surface().get_graphics_driver().is_vsync_enabled(), 
            0
        );
    }

    void d3d11_renderer::handle_resize(const float width, const float height)
    {
        d3d11_instance::get_singleton().cleanup_render_target();
        d3d11_instance::get_singleton().get_swap_chain()->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
        d3d11_instance::get_singleton().create_render_target();

        depth_stencil_buffer_.destroy();
        depth_stencil_buffer_.allocate();
    }
}