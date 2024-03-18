#include "d3d11_sampler.h"

#include "d3d11_instance.h"

namespace lumina
{
	bool d3d11_sampler::allocate()
	{
        if (is_allocated())
            return false;

        D3D11_SAMPLER_DESC sampler_descriptor;
        ZeroMemory(&sampler_descriptor, sizeof(sampler_descriptor));
        sampler_descriptor.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        sampler_descriptor.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_descriptor.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_descriptor.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_descriptor.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampler_descriptor.MinLOD = 0;
        sampler_descriptor.MaxLOD = D3D11_FLOAT32_MAX;

        return !FAILED(d3d11_instance::get_singleton().get_device()->CreateSamplerState(&sampler_descriptor, &d3d_sampler_state_));
	}

    bool d3d11_sampler::allocate(const D3D11_SAMPLER_DESC& sampler_descriptor)
    {
        if (is_allocated())
            return false;

        return !FAILED(d3d11_instance::get_singleton().get_device()->CreateSamplerState(&sampler_descriptor, &d3d_sampler_state_));
    }

    void d3d11_sampler::enable() const
    {
        if (!is_allocated())
            return;

        d3d11_instance::get_singleton().get_device_context()->PSSetSamplers(0, 1, &d3d_sampler_state_);
    }
}