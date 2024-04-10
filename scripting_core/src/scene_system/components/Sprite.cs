using System.Runtime.CompilerServices;

namespace Lumina
{
    public class Sprite : Component
    {
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
