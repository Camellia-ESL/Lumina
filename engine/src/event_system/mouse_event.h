#pragma once

#include "event_base.h"

namespace lumina
{
	enum class mouse_event_types_e
	{
		MOUSE_CURSOR_MOVE,
		MOUSE_JOINED_WINDOW_AREA,
		MOUSE_LEFT_WINDOW_AREA,

		// Mouse button pressed, released or repeated
		MOUSE_BUTTON_CLICK,

		// Mouse wheel scrolling event
		MOUSE_WHEEL_SCROLL
	};

	enum class mouse_button_types_e
	{
		MOUSE_BUTTON_LEFT = 0,   
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_LAST   
	};

	struct mouse_event_t : public event_t
	{
		mouse_event_types_e mouse_event_subtype;
		
		mouse_button_types_e mouse_button;
		input_action_types_e action_type;
		
		double cursor_pos_x;
		double cursor_pos_y;

		// Usually not used (the default wheel scroll usually gets stored in mouse_wheel_y)
		double mouse_wheel_x;

		// The default mouse wheel offset scalar (positive value = scroll up, negative value = scroll down)
		double mouse_wheel_y;
	};
}