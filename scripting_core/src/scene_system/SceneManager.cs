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
        public static Scene GetScene(string name)
        {
            Scene sceneBuffer = new Scene();

            if(!GetSceneImpl(name, ref sceneBuffer))
                return null;

            return sceneBuffer;
        }

        /// <summary>
        /// Creates a Scene with a given name (NOTE: If a scene with this name already exist it get's not created and return false)
        /// </summary>
        /// <param name="name">name</param>
        /// <returns>Wheter if the scene was created or not</returns>
        public static bool CreateScene(string name)
        {
            return CreateSceneImpl(name);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool GetSceneImpl(string name, ref Scene sceneOut);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool CreateSceneImpl(string name);
    }
}
