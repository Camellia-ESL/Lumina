#pragma once

#include <cstdint>

namespace lumina
{
	// Helper memory class 
	class lumina_memory_s
	{
	public:

		static constexpr const uint64_t BYTE_SIZE = 0x1;
		static constexpr const uint64_t KILO_BYTE_SIZE = BYTE_SIZE * 1024;
		static constexpr const uint64_t MEGA_BYTE_SIZE = KILO_BYTE_SIZE * 1024;
		static constexpr const uint64_t GIGA_BYTE_SIZE = MEGA_BYTE_SIZE * 1024;
		static constexpr const uint64_t TERA_BYTE_SIZE = GIGA_BYTE_SIZE * 1024;

		// Get's the allocated virtual memory usage size (in BYTE)
		static uint64_t get_virtual_memory_usage();

	};
}