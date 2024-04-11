using System.Runtime.CompilerServices;

namespace Lumina
{
    /// <summary>
    /// The sprite component that handles 2D picture rendering in Lumina for every entity
    /// </summary>
    public class Sprite : Component
    {
        /// <summary>
        /// The default color used when no assets are applied to the sprite
        /// </summary>
        public Vec4 Color { get => GetColor(); }

        private Vec4 GetColor()
        {
            Vec4 resBuffer = new Vec4();
            GetColorImpl(OwnerEntity, ref resBuffer);
            return resBuffer;
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void GetColorImpl(Entity ownerEntity, ref Vec4 outVec);
    }
}
