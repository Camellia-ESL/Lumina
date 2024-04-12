namespace Lumina
{
    /// <summary>
    /// All the mouse event possible
    /// </summary>
    public enum MouseEventType
    {
        MOUSE_CURSOR_MOVE,
		MOUSE_JOINED_WINDOW_AREA,
		MOUSE_LEFT_WINDOW_AREA,
		MOUSE_BUTTON_CLICK,
		MOUSE_WHEEL_SCROLL
    };

    /// <summary>
    /// All the mouse buttons
    /// </summary>
    public enum MouseButtonType
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

    /// <summary>
	/// Represent a Mouse Event callback called every time a mouse event has been fired
	/// </summary>
    public class MouseEvent : EventBase
    {
        /// <summary>
        /// The mouse event type 
        /// </summary>
        public MouseEventType MouseEventType { get => _mouseEventType; }
        
        /// <summary>
        /// The eventual mouse button involved in the event
        /// </summary>
        public MouseButtonType Button { get => _button; }

        /// <summary>
        /// The action type that happened in the event
        /// </summary>
        public EventInputActionType ActionType { get => _actionType; }

        /// <summary>
        /// The cursor position X on the screen if the event fired was a MOUSE_CURSOR_MOVE event
        /// </summary>
        public double CursorPosX { get => _cursorPosX; }
        
        /// <summary>
        /// The cursor position Y on the screen if the event fired was a MOUSE_CURSOR_MOVE event
        /// </summary>
        public double CursorPosY { get => _cursorPosY; }

        /// <summary>
        /// The mouse wheel X offset if the event fired was a MOUSE_WHEEL_SCROLL event
        /// </summary>
        public double MouseWheelX { get => _mouseWheelX; }

        /// <summary>
        /// The mouse wheel Y offset if the event fired was a MOUSE_WHEEL_SCROLL event
        /// </summary>
        public double MouseWheelY { get => _mouseWheelY; }

        private MouseEventType _mouseEventType;
        private MouseButtonType _button;
        private EventInputActionType _actionType;
        private double _cursorPosX;
        private double _cursorPosY;
        private double _mouseWheelX;
        private double _mouseWheelY;
    }

    /// <summary>
	/// Represent a Keyboard Event callback called every time a keyboard event has been fired
	/// </summary>
    public class MouseEventCallback : EventCallback<MouseEvent>
    {
        public MouseEventCallback(CallbackFunc callback) : base(callback)
        {
        }

        // The event caller (called from internal when a mouse event is fired)
        private void Dispatch()
        {
            _callbackHolder(_event);
        }
    }
}
