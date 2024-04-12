using System;

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

    /// <summary>
    /// The base class for all the event callbacks
    /// </summary>
    public class EventCallback<EventType> where EventType : EventBase, new()
    {
        /// <summary>
        /// The function definition of the callback to execute when an event is fired
        /// </summary>
        /// <param name="e">The event</param>
        public delegate void CallbackFunc(EventType e);

        /// <summary>
        /// A optional tag that can be set to identify the event callback
        /// </summary>
        public string Tag { get; set; } = "";

        public EventCallback(CallbackFunc callback)
        {
            _callbackHolder = callback;
        }

        // The holder of the callee (callback)
        protected CallbackFunc _callbackHolder;
        // The event that happened that will be passed in the callee (callback)
        protected EventType _event = new EventType();
    }
}
