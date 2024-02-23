#include "ui_render.h"

#include "view_register.h"

// Editor views (always visible views, editor panels, scene panels, etc..)
#include "views/profiler_view.h"
#include "views/scenes_visualizer_view.h"
#include "views/top_window_toolbar_view.h"
#include "views/scene_grid_view.h"

#include "../editor_compile_configs.h"

#include "app/app.h"
#include "graphics/d3d11_api/d3d11_instance.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGuizmo/ImGuizmo.h"

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

        // Setup UI Style and Default Colors
        ImGui::GetIO().Fonts->AddFontFromFileTTF(LUMINA_EDITOR_RESOURCES_PATH"fonts/sf_pro_bold.otf", 14.0f);

        // Style setup
        auto style = &ImGui::GetStyle();

        style->WindowPadding = ImVec2(15, 15);
        style->FramePadding = ImVec2(5, 5);
        style->FrameRounding = 12.0f;
        style->ItemSpacing = ImVec2(12, 8);
        style->ItemInnerSpacing = ImVec2(8, 6);
        style->IndentSpacing = 25.0f;
        style->ScrollbarSize = 15.0f;
        style->ScrollbarRounding = 9.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 3.0f;
        style->PopupRounding = 4.0f;

        //Colors setup
        style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.46f, 0.46f, 0.46f, 1.0f);
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        style->Colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2f, 0.2f, 0.2f, 0.75f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.65f, 0.55f, 0.4f, 0.31f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.75f, 0.65f, 0.4f, 1.0f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.0f, 0.8f, 0.4f, 1.0f);
        style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.80f, 0.31f);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.80f, 0.31f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.23f, 0.24f, 1.00f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_Header] = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.29f, 0.29f, 0.33f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.31f, 0.31f, 0.34f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3f);
        style->Colors[ImGuiCol_Tab] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
        style->Colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);
        style->Colors[ImGuiCol_TabHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
        style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
        style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);
        style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
        style->Colors[ImGuiCol_Separator] = ImVec4(0.2f, 0.2f, 0.2f, 0.0f);
        style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
        style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOther(
            editor_app_player::get_singleton().get_surface().get_desktop_handler(),
            true
        );

        ImGui_ImplDX11_Init(
            lumina::d3d11_instance::get_singleton().get_device(),
            lumina::d3d11_instance::get_singleton().get_device_context()
        );

        // Inits the editor views
        view_register_s::register_view(std::make_shared<profiler_view>());
        view_register_s::register_view(std::make_shared<scenes_visualizer_view>());
        view_register_s::register_view(std::make_shared<top_window_toolbar_view>());
        view_register_s::register_view(std::make_shared<scene_grid_view>());
	}

	void ui_render_s::on_render()
	{
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Begin ImGuizmo frame
        ImGuizmo::BeginFrame();
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

        // Setup Dockspace for this frame
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_AutoHideTabBar;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin("Dockspace Window", NULL, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2{ 0.0f, 0.0f }, ImGuiDockNodeFlags_PassthruCentralNode);

        // Render all the registerd views
        view_register_s::render_views();

        // ImGui End frame render 
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