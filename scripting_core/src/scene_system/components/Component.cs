namespace Lumina
{
    public class Component
    {
        /// <summary>
        /// The entity in which the component is attached to
        /// </summary>
        public Entity OwnerEntity { get => _ownerEntity; set { _ownerEntity = value; } }

        private Entity _ownerEntity = null;
    }
}
