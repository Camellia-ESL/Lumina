using System.Runtime.CompilerServices;

namespace Lumina
{
    /// <summary>
    /// Lumina official Console Logger
    /// </summary>
    public static class Logger
    {
        /// <summary>
        /// Logs a simple info message with date format and info colored
        /// </summary>
        /// <param name="msg">msg</param>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void LogInfo(string msg);

        /// <summary>
        /// Logs a simple warning message with date format and warning colored
        /// </summary>
        /// <param name="msg">msg</param>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void LogWarning(string msg);

        /// <summary>
        /// Logs a simple error message with date format and error colored
        /// </summary>
        /// <param name="msg">msg</param>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void LogError(string msg);
    }
}
