using System.Runtime.CompilerServices;

namespace Lumina
{
    /// <summary>
    /// Transform Component, reflects the object world 3D position, orientation and scale
    /// </summary>
    public class Transform : Component
    {
        /// <summary>
        /// The transform 3D position in the world
        /// </summary>
        public Vec3 Position 
        { 
            get => GetPosition();
            set 
            { 
                SetPosition(value);
            }
        }

        /// <summary>
        /// The transform Euler Angle Axis (rotation) in degrees
        /// </summary>
        public Vec3 EulerAnglesRotation { get => GetEulerAnglesRotation(); }

        /// <summary>
        /// The transform 3D local scaling
        /// </summary>
        public Vec3 Scale 
        { 
            get => GetScale(); 
            set 
            { 
                SetScale(value);
            } 
        }

        /// <summary>
        /// Set the transform position
        /// </summary>
        /// <param name="pos">The new position</param>
        public void SetPosition(Vec3 pos)
        {
            SetPositionImpl(OwnerEntity, pos);
        }

        /// <summary>
        /// Rotate the transform by a given angle (degrees) on the 3 rotation axis (note it rotates not set the rotation)
        /// </summary>
        /// <param name="rot">The rotation axis</param>
        /// <param name="angle">The angle to apply (degrees)</param>
        public void Rotate(Vec3 rot, float angle)
        {
            RotateImpl(OwnerEntity, rot, angle);
        }

        /// <summary>
        /// Set the transform scale
        /// </summary>
        /// <param name="scale">The new scale</param>
        public void SetScale(Vec3 scale)
        {
            SetScaleImpl(OwnerEntity, scale);
        }

        private Vec3 GetPosition()
        {
            Vec3 resBuffer = new Vec3();
            GetPositionImpl(OwnerEntity, ref resBuffer);
            return resBuffer;
        }

        private Vec3 GetEulerAnglesRotation()
        {
            Vec3 resBuffer = new Vec3();
            GetEulerAnglesRotationImpl(OwnerEntity, ref resBuffer);
            return resBuffer;
        }

        private Vec3 GetScale() 
        {
            Vec3 resBuffer = new Vec3();
            GetScaleImpl(OwnerEntity, ref resBuffer);
            return resBuffer;
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void GetPositionImpl(Entity ownerEntity, ref Vec3 outVec);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void GetEulerAnglesRotationImpl(Entity ownerEntity, ref Vec3 outVec);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void GetScaleImpl(Entity ownerEntity, ref Vec3 outVec);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void SetPositionImpl(Entity ownerEntity, Vec3 vec);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void RotateImpl(Entity ownerEntity, Vec3 vec, float angle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private static extern void SetScaleImpl(Entity ownerEntity, Vec3 vec);
    }
}
