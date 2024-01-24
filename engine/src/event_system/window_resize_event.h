#pragma once

#include "event_base.h"

namespace lumina
{
	struct window_resize_event_t : public event_t
	{
		int app_width, app_height;
	};
}