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
        /// The registry this entity belongs to (mostly useless, shouldn't be accessed)
        /// </summary>
        public ulong RegistryPtr { get => _registryPtr; }

        public ComponentType GetComponent<ComponentType>() where ComponentType : new()
        {
            // Creates a buffer for the result component and packs everything for the request
            ComponentType componentBuffer = new ComponentType();
            object componentPackage = componentBuffer;

            // Execute the internal request
            if (!GetComponentImpl(Id, _registryPtr, ref componentPackage))
                return default;

            // Unpacks the package sent in the internal request
            componentBuffer = (ComponentType)componentPackage;

            return componentBuffer;
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern bool GetComponentImpl(uint entityId, ulong entityRegPtr, ref object componentOut);

        private ulong _registryPtr = 0x0;
        private uint _id = 0;
    }
}
