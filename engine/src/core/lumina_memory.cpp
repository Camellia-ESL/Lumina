#include "lumina_memory.h"

#ifdef LUMINA_WIN32_PLATFORM
#include <Windows.h>
#include <psapi.h>
#endif 


namespace lumina
{
	uint64_t lumina_memory_s::get_virtual_memory_usage()
	{
#ifdef LUMINA_WIN32_PLATFORM
		PROCESS_MEMORY_COUNTERS counters;
		if (GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters)))
			return counters.WorkingSetSize;
		else
			return 0;
#else 
		return 0;
#endif 
	}
}