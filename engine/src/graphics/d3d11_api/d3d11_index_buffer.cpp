#include "d3d11_index_buffer.h"

#include "spdlog/spdlog.h"

namespace lumina
{
	bool d3d11_index_buffer::allocate(const std::vector<uint32_t>& indicies)
	{
		// Check if the buffer is already allocated
		if (is_allocated())
			return false;

		indicies_array_data_ = indicies;
		index_buffer_size_ = sizeof(uint32_t) * indicies.size();

		D3D11_BUFFER_DESC buffer_alloc_info;
		ZeroMemory(&buffer_alloc_info, sizeof(buffer_alloc_info));
		buffer_alloc_info.Usage = D3D11_USAGE_DEFAULT;
		buffer_alloc_info.ByteWidth = index_buffer_size_;
		buffer_alloc_info.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer_alloc_info.CPUAccessFlags = NULL;

		D3D11_SUBRESOURCE_DATA index_buffer_data;
		index_buffer_data.pSysMem = &indicies_array_data_[0];
		
		d3d11_instance::get_singleton().get_device()->CreateBuffer(&buffer_alloc_info, &index_buffer_data, &index_buffer_);
		
		return is_allocated();
	}

	void d3d11_index_buffer::enable() const
	{
		d3d11_instance::get_singleton().get_device_context()->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	}
}