#include "d3d11_texture.h"

#include "d3d11_instance.h"

#include "D3D11X/D3DX11tex.h"

namespace lumina
{
    bool d3d11_texture::load_from_file(const std::string& file_path)
    {
        if (is_allocated())
            return false;
        
        return !FAILED(D3DX11CreateShaderResourceViewFromFile(
            d3d11_instance::get_singleton().get_device(), 
            file_path.c_str(), 
            nullptr, 
            nullptr, 
            &texture_, 
            nullptr
        ));
    }

    bool d3d11_texture::load_from_memory(void* img_data, l_uint32 data_size)
    {
        if (is_allocated())
            return false;

        return !FAILED(D3DX11CreateShaderResourceViewFromMemory(
            d3d11_instance::get_singleton().get_device(),
            img_data,
            data_size,
            nullptr,
            nullptr,
            &texture_,
            nullptr
        ));
    }

    bool d3d11_texture::enable(const uint32_t slot) const
    {
        if (!is_allocated())
            return false;

        d3d11_instance::get_singleton().get_device_context()->PSSetShaderResources(slot, 1, &texture_);
    }
}