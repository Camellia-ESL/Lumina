#include "ui_render.h"

#include "app/app.h"

#include "graphics/d3d11_api/d3d11_instance.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_glfw.h"

namespace lumina_editor
{
	
	void ui_render_s::on_init()
	{
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOther(
            editor_app_player::get_singleton().get_surface().get_desktop_handler(), 
            true
        );

        ImGui_ImplDX11_Init(
            lumina::d3d11_instance::get_singleton().get_device(), 
            lumina::d3d11_instance::get_singleton().get_device_context()
        );
	}

	void ui_render_s::on_render()
	{
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test");
        ImGui::End();

        // Rendering
        ImGui::Render();

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
	}

}