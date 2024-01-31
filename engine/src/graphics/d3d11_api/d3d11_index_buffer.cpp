#include "d3d11_index_buffer.h"

#include "spdlog/spdlog.h"

namespace lumina
{
	bool d3d11_index_buffer::allocate(uint32_t size)
	{
		// Check if the buffer is already allocated
		if (is_allocated())
			return false;

		D3D11_BUFFER_DESC buffer_alloc_info;
		ZeroMemory(&buffer_alloc_info, sizeof(buffer_alloc_info));
		buffer_alloc_info.Usage = D3D11_USAGE_DYNAMIC;
		buffer_alloc_info.ByteWidth = size;
		buffer_alloc_info.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer_alloc_info.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		d3d11_instance::get_singleton().get_device()->CreateBuffer(&buffer_alloc_info, nullptr, &index_buffer_);
		
		return is_allocated();
	}

	void d3d11_index_buffer::push_indicies(const std::vector<uint32_t>& indicies)
	{
		if (!is_allocated())
		{
			spdlog::error("D3D11 Index Buffer -> Trying to update data to a non allocated buffer");
			return;
		}

		// Adds indicies to the array
		indicies_array_data_.insert(indicies_array_data_.end(), indicies.begin(), indicies.end());
		
		// Upload the updated array to the index buffer
		load_data(&indicies_array_data_[0], sizeof(indicies_array_data_));
	}

	void d3d11_index_buffer::pop_index()
	{
		if (!is_allocated())
		{
			spdlog::error("D3D11 Index Buffer -> Trying to update data to a non allocated buffer");
			return;
		}

		// Remove the last item
		indicies_array_data_.pop_back();

		// Upload the updated array to the index buffer
		load_data(&indicies_array_data_[0], sizeof(indicies_array_data_));
	}

	void d3d11_index_buffer::enable() const
	{
		d3d11_instance::get_singleton().get_device_context()->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	}


	void d3d11_index_buffer::load_data(const void* data, uint32_t size) const
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		d3d11_instance::get_singleton().get_device_context()->Map(index_buffer_, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, data, size);
		d3d11_instance::get_singleton().get_device_context()->Unmap(index_buffer_, NULL);
	}
}