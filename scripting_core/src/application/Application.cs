using System.Runtime.CompilerServices;

namespace Lumina
{
    /// <summary>
    /// The main Application class of the program, also the entry point
    /// </summary>
    public class Application
    {
        /// <summary>
        /// The application delta time
        /// </summary>
        public static float DeltaTime { get => GetDeltaTime(); }

        /// <summary>
        /// Called once at application start
        /// </summary>
        public virtual void OnStart() { }

        /// <summary>
        /// Called once every frame
        /// </summary>
        public virtual void OnUpdate() { }

        /// <summary>
        /// Get the application delta time, usefull to normalize speeds
        /// </summary>
        /// <returns>The delta time</returns>
        public static float GetDeltaTime()
        { 
            return GetDeltaTimeImpl(); 
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern float GetDeltaTimeImpl();
    }
}