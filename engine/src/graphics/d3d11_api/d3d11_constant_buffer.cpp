#include "d3d11_constant_buffer.h"

namespace lumina
{
	 
	bool d3d11_constant_buffer::allocate(uint32_t size)
	{
		D3D11_BUFFER_DESC buffer_alloc_info;
		ZeroMemory(&buffer_alloc_info, sizeof(buffer_alloc_info));
		buffer_alloc_info.Usage = D3D11_USAGE_DYNAMIC;
		buffer_alloc_info.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buffer_alloc_info.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		buffer_alloc_info.ByteWidth = size;
		
		d3d11_instance::get_singleton().get_device()->CreateBuffer(&buffer_alloc_info, NULL, &constant_buffer_);

		return is_allocated();
	}

	void d3d11_constant_buffer::load_data(const void* data, uint32_t size) const
	{
		D3D11_MAPPED_SUBRESOURCE constant_buffer_mapped_resource;
		d3d11_instance::get_singleton().get_device_context()->Map(constant_buffer_, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &constant_buffer_mapped_resource);
		memcpy(constant_buffer_mapped_resource.pData, data, size);
		d3d11_instance::get_singleton().get_device_context()->Unmap(constant_buffer_, NULL);
	}

	void d3d11_constant_buffer::enable(uint32_t slot) const
	{
		if (!is_allocated())
			return;

		d3d11_instance::get_singleton().get_device_context()->VSSetConstantBuffers(slot, 1, &constant_buffer_);
	}
}