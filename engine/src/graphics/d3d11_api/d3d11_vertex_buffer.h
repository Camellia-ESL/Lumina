#pragma once

#include "d3d11_instance.h"

#include <vector>

namespace lumina
{
	struct d3d11_vertex_buffer_alloc_info_t
	{
		// The size of the vertex buffer [Required]
		uint32_t buffer_size = 0;

		// The topology that will be used for rendering (default to TRIANGLE_LIST) [Optional]
		D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		// A pointer to the data to load in the vertex buffer [Optional]
		void* data_to_load = nullptr;

		// The size of the data to load [Optional]
		uint32_t data_to_load_size = 0;
	};

	class d3d11_vertex_buffer
	{
	public:

		d3d11_vertex_buffer() {}

		// Allocates the vertex buffer and eventually load the given data into it
		bool allocate(const d3d11_vertex_buffer_alloc_info_t& alloc_info);

		// Load data in the buffer
		void load_data(const void* data, uint32_t size);

		// Enable the vertex buffer to be used in the render pass
		void enable();

		// Set the stride of the vertex buffer (the size of the type of a single chunk of data of the vertex buffer)
		void set_stride(const uint32_t stride) { vertex_stride_ = stride; }

		const bool is_allocated() const { return vertex_buffer_ != nullptr; }
		const uint32_t get_stride() const { return vertex_stride_; }
		const D3D11_PRIMITIVE_TOPOLOGY get_topology() const { return topology_; }

	private:

		ID3D11Buffer* vertex_buffer_ = nullptr;
		uint32_t vertex_stride_ = 0;

		// @enhancement-[Graphics]: Topology property should really be moved somewhere else.
		D3D11_PRIMITIVE_TOPOLOGY topology_; 

	};
}