using System.Runtime.CompilerServices;

namespace Lumina
{
    public class Transform : Component
    {
        public Vec3 Position { get => GetPosition(); }
        public Vec3 Rotation { get => new Vec3(); }
        public Vec3 Scale { get => new Vec3(); }

        private Vec3 GetPosition()
        {
            Vec3 resBuffer = new Vec3();
            GetPositionImpl(OwnerEntity, ref resBuffer);
            return resBuffer;
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void GetPositionImpl(Entity ownerEntity, ref Vec3 outVec);
    }
}
