using System.Runtime.CompilerServices;
using System.Xml.Linq;

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

        /// <summary>
        /// Switch the active Scene with another scene
        /// </summary>
        /// <param name="name">The scene name</param>
        /// <returns>Wheter if the scene has switched or not</returns>
        public static bool SwitchScene(string name)
        {
            return SwitchSceneImpl(name);
        }

        /// <summary>
        /// Switch the active Scene with another scene
        /// </summary>
        /// <param name="scene">The scene to switch</param>
        /// <returns>Wheter if the scene has switched or not</returns>
        public static bool SwitchScene(Scene scene) 
        {
            return SwitchSceneImpl(scene.Name);
        }

        /// <summary>
        /// Safely destroy's a Scene and free the memory(if the scene passed is the active scene it get's automatically deactivated and destroyed)
        /// </summary>
        /// <param name="name">The scene name</param>
        /// <returns>Wheter if the scene was destroyed or not</returns>
        public static bool DestroyScene(string name)
        {
            return DestroySceneImpl(name);
        }

        /// <summary>
        /// Safely destroy's a Scene and free the memory (if the scene passed is the active scene it get's automatically deactivated and destroyed)
        /// </summary>
        /// <param name="name">The scene to destroy</param>
        /// <returns>Wheter if the scene was destroyed or not</returns>
        public static bool DestroyScene(Scene scene) 
        {
            return DestroyScene(scene.Name);
        }

        /// <summary>
        /// Clear the SceneManager, destroy's every scene and free all the memory (optimized, suggest to be used instead of manually deleting all scenes)
        /// </summary>
        public static void DestroyAll()
        {
            DestroyAllImpl();
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool GetSceneImpl(string name, ref Scene sceneOut);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool CreateSceneImpl(string name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool SwitchSceneImpl(string name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool DestroySceneImpl(string name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool DestroyAllImpl();
    }
}
