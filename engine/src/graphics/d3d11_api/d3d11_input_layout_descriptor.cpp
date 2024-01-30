#include "d3d11_input_layout_descriptor.h"

#include "d3d11_instance.h"

#include "spdlog/spdlog.h"

namespace lumina
{
	bool d3d11_input_layout_descriptor::allocate(d3d11_shader* shader, const std::vector<D3D11_INPUT_ELEMENT_DESC>& descriptor)
	{
		if (shader->get_blob() == nullptr)
		{
			spdlog::error("D3D11 Input Layout Descriptor -> Trying to access a non allocated shader.");
			return false;
		}

		if (descriptor.size() < 1)
		{
			spdlog::error("D3D11 Input Layout Descriptor -> Trying to allocate a descriptor without passing descriptor elements.");
			return false;
		}

		input_elements_descriptor_ = descriptor;

		if (FAILED(
			d3d11_instance::get_singleton().get_device()->CreateInputLayout(
				&descriptor[0],
				descriptor.size(),
				shader->get_blob()->GetBufferPointer(),
				shader->get_blob()->GetBufferSize(),
				&input_layout_
			)
		))
		{
			spdlog::error("D3D11 Input Layout Descriptor -> Error creating the input layout descriptor");
			return false;
		}

		return is_allocated();
	}

	void d3d11_input_layout_descriptor::enable() const
	{
		if (!is_allocated())
			return;

		d3d11_instance::get_singleton().get_device_context()->IASetInputLayout(input_layout_);
	}

}