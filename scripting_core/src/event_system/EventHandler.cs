using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;

namespace Lumina
{
    /// <summary>
    /// The event handler of Lumina, handles every internal input event such as Keyboard, Mouse, Surface and more events
    /// </summary>
    public class EventHandler
    {
        /// <summary>
        /// Return true if the key is pressed in the current state
        /// </summary>
        /// <returns>Wheter if the key is pressed</returns>
        public static bool IsKeyPressed(KeyboardKeyType key)
        { 
            return IsKeyPressedImpl(key);
        }

        /// <summary>
        /// Return true if the key is released in the current state
        /// </summary>
        /// <returns>Wheter if the key is released</returns>
        public static bool IsKeyReleased(KeyboardKeyType key)
        {
            return IsKeyReleasedImpl(key);
        }

        /// <summary>
        /// Return true if the key is held in the current state
        /// </summary>
        /// <returns>Wheter if the key is held</returns>
        public static bool IsKeyHeld(KeyboardKeyType key)
        {
            return IsKeyHeldImpl(key);
        }

        public static void RegisterEventCallback<CallbackType>(CallbackType callback)
        {
            // Creates a buffer for the CallbackType and packs everything for the request
            _callesRegister.Add(callback);

            // Request the event listener to register the callee to be fired whenever a event is fired
            RegisterEventCallbackImpl(callback);
        }

        // Holds all the calles registered
        private static List<object> _callesRegister = new List<object>();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool IsKeyPressedImpl(KeyboardKeyType key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool IsKeyReleasedImpl(KeyboardKeyType key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool IsKeyHeldImpl(KeyboardKeyType key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void RegisterEventCallbackImpl(object callback);
    }
}
