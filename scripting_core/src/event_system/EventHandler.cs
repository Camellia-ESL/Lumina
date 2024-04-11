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

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool IsKeyPressedImpl(KeyboardKeyType key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool IsKeyReleasedImpl(KeyboardKeyType key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool IsKeyHeldImpl(KeyboardKeyType key);
    }
}
