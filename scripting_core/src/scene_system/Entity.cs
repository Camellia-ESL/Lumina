using System;
using System.Runtime.CompilerServices;

namespace Lumina
{
    public class Entity
    {
        /// <summary>
        /// The entity id
        /// </summary>
        public uint Id { get => _id; }

        /// <summary>
        /// The registry this entity belongs to
        /// </summary>
        public ulong RegistryPtr { get => _registryPtr; }

        /// <summary>
        /// Get's a component attached to the entity
        /// </summary>
        /// <typeparam name="ComponentType">The component type (es. Transform)</typeparam>
        /// <returns>The component attached</returns>
        public ComponentType GetComponent<ComponentType>() where ComponentType : Component, new()
        {
            // Creates a buffer for the result component and packs everything for the request
            ComponentType componentBuffer = new ComponentType();
            object componentPackage = componentBuffer;

            // Execute the internal request
            if (!GetComponentImpl(Id, RegistryPtr, ref componentPackage))
                return null;

            // Unpacks the package sent in the internal request
            componentBuffer = (ComponentType)componentPackage;
            componentBuffer.OwnerEntity = this;

            return componentBuffer;
        }

        /// <summary>
        /// Attach a new component to the entity
        /// </summary>
        /// <typeparam name="ComponentType">The component type to attach (es Transform)</typeparam>
        /// <returns>The attached component</returns>
        public ComponentType AddComponent<ComponentType>() where ComponentType : Component, new()
        {
            // Creates a buffer for the result component and packs everything for the request
            ComponentType componentBuffer = new ComponentType();
            object componentPackage = componentBuffer;

            // Execute the internal request
            if (!AddComponentImpl(Id, RegistryPtr, ref componentPackage))
                return null;

            // Unpacks the package sent in the internal request
            componentBuffer = (ComponentType)componentPackage;
            componentBuffer.OwnerEntity = this;

            return componentBuffer;
        }

        /// <summary>
        /// Wheter if the entity has a certain component attached
        /// </summary>
        /// <typeparam name="ComponentType">The component to check</typeparam>
        /// <returns>True if it has the component</returns>
        public bool HasComponent<ComponentType>() where ComponentType : Component, new()
        {
            // Creates a buffer for the result component and packs everything for the request
            ComponentType componentBuffer = new ComponentType();
            object componentPackage = componentBuffer;

            // Execute the internal request
            return HasComponentImpl(Id, RegistryPtr, componentPackage);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool GetComponentImpl(uint entityId, ulong entityRegPtr, ref object componentOut);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool AddComponentImpl(uint entityId, ulong entityRegPtr, ref object componentOut);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool HasComponentImpl(uint entityId, ulong entityRegPtr, object componentOut);

        private ulong _registryPtr = 0x0;
        private uint _id = 0;
    }
}
