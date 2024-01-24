#include "d3d11_instance.h"

namespace lumina
{
    d3d11_instance* d3d11_instance::instance_ = nullptr;

    // Helper functions
    bool d3d11_instance::create_device(HWND hwnd)
    {
        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &swap_chain_, &device_, &featureLevel, &device_context_);
        if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
            res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &swap_chain_, &device_, &featureLevel, &device_context_);
        if (res != S_OK)
            return false;

        create_rendere_target();
        return true;
    }

    void d3d11_instance::cleanup_device()
    {
        cleanup_render_target();
        if (swap_chain_) { swap_chain_->Release(); swap_chain_ = nullptr; }
        if (device_context_) { device_context_->Release(); device_context_ = nullptr; }
        if (device_) { device_->Release(); device_ = nullptr; }
    }

    void d3d11_instance::create_rendere_target()
    {
        ID3D11Texture2D* pBackBuffer;
        swap_chain_->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        device_->CreateRenderTargetView(pBackBuffer, nullptr, &main_render_target_view_);
        pBackBuffer->Release();
    }

    void d3d11_instance::cleanup_render_target()
    {
        if (main_render_target_view_) { main_render_target_view_->Release(); main_render_target_view_ = nullptr; }
    }
}