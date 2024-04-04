using System.Runtime.CompilerServices;

namespace Lumina
{
    public static class SceneManager
    {
        /// <summary>
        /// Search a Scene by its name
        /// </summary>
        /// <param name="name">The scene name</param>
        /// <returns>The scene instance</returns>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern Scene GetScene(string name);

        /// <summary>
        /// Creates a Scene with a given name (NOTE: If a scene with this name already exist it get's not created and return false)
        /// </summary>
        /// <param name="name">name</param>
        /// <returns>Wheter if the scene was created or not</returns>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern bool CreateScene(string name);
    }
}
