namespace Lumina
{
    /// <summary>
    /// All the event types
    /// </summary>
    public enum EventType
    {
        MOUSE_EVENT,
		KEYBOARD_EVENT,
        WINDOW_RESIZE_EVENT
    };

    /// <summary>
    /// All the possible input action types (for keyboard and mouse)
    /// </summary>
    public enum EventInputActionType
    {
        ACTION_RELEASE = 0,
		ACTION_PRESS,
		ACTION_REPEAT
    };

    /// <summary>
    /// Represent the base event type for all Lumina Internal events 
    /// </summary>
    public class EventBase
    {
        /// <summary>
        /// The event type
        /// </summary>
        public EventType EventType { get => _eventType; }

        private EventType _eventType;
    }
}
