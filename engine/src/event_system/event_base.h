#pragma once

namespace lumina
{
	enum class event_types_e
	{
		MOUSE_EVENT_,
		KEYBOARD_EVENT_
	};

	enum class input_action_types_e
	{
		ACTION_RELEASE = 0,
		ACTION_PRESS,
		ACTION_REPEAT
	};

	// Represent a base event type
	struct event_t
	{
		event_types_e event_type;
	};
}