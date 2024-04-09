namespace Lumina
{
    public class Identifier : Component
    {
        /// <summary>
        /// The entity UUID
        /// </summary>
        public string Id { get => _id; }

        /// <summary>
        /// The entity name
        /// </summary>
        public string Name { get => _name; }

        private string _id = "";
        private string _name = "";
    }
}
