using System.Runtime.CompilerServices;

namespace Lumina
{
    public class Scene
    {
        public string Name { get; set; } = "";

        /// <summary>
        /// Add's a new entity into the scene
        /// </summary>
        /// <returns>The new entity or null if it fails</returns>
        public Entity CreateEntity()
        {
            Entity entityBuffer = new Entity();

            if (!CreateEntityImpl(Name, ref entityBuffer))
                return null;

            return entityBuffer;
        }

        /// <summary>
        /// Return the first entity found with the given name or null
        /// </summary>
        /// <param name="name">The entity name</param>
        /// <returns>The entity or null if it fails</returns>
        public Entity GetEntityByName(string name)
        {
            Entity entityBuffer = new Entity();

            if (!GetEntityByNameImpl(Name, name, ref entityBuffer))
                return null;

            return entityBuffer;
        }

        /// <summary>
        /// Destroy a given entity from the scene
        /// </summary>
        /// <param name="entity">The entity to destroy</param>
        public void DestroyEntity(Entity entity)
        {
            DestroyEntityImpl(Name, entity);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool CreateEntityImpl(string sceneName, ref Entity entityOut);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool GetEntityByNameImpl(string sceneName, string entityName, ref Entity entityOut);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void DestroyEntityImpl(string sceneName, Entity entity);
    }
}
