namespace Lumina
{
    /// <summary>
    /// A representation of 2 float values (x,y) (r,g)
    /// </summary>
    public class Vec2
    {
        // Spatial Mode Definitions
        public float X { get => _x; set { _x = value; } }
        public float Y { get => _y; set { _y = value; } }

        // Color Mode Definitions
        public float R { get => _x; set { _x = value; } }
        public float G { get => _y; set { _y = value; } }

        public Vec2() { }
        public Vec2(float x, float y) { _x = x; _y = y; }

        /// <summary>
        /// Sum two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The sum</returns>
        public static Vec2 Sum(Vec2 a, Vec2 b)
        {
            return new Vec2(a.X + b.X, a.Y + b.Y);
        }

        /// <summary>
        /// Subtract's two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The subtraction</returns>
        public static Vec2 Subtract(Vec2 a, Vec2 b)
        {
            return new Vec2(a.X - b.X, a.Y - b.Y);
        }

        /// <summary>
        /// Multiplie's two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The multiplication</returns>
        public static Vec2 Multiply(Vec2 a, Vec2 b)
        {
            return new Vec2(a.X * b.X, a.Y * b.Y);
        }

        /// <summary>
        /// Divide's to vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The divide result</returns>
        public static Vec2 Divide(Vec2 a, Vec2 b)
        {
            return new Vec2(a.X / b.X, a.Y / b.Y);
        }

        public static Vec2 operator +(Vec2 a, Vec2 b)
        {
            return Sum(a, b);
        }

        public static Vec2 operator -(Vec2 a, Vec2 b)
        {
            return Subtract(a, b);
        }

        public static Vec2 operator *(Vec2 a, Vec2 b)
        {
            return Multiply(a, b);
        }

        public static Vec2 operator /(Vec2 a, Vec2 b)
        {
            return Divide(a, b);
        }

        public override string ToString()
        {
            return $"(x: {X}, y: {Y})";
        }

        private float _x = 0.0f;
        private float _y = 0.0f;
    }

    /// <summary>
    /// A representation of 3 float values (x,y,z) (r,g,b)
    /// </summary>
    public class Vec3
    {
        // Spatial Mode Definitions
        public float X { get => _x; set { _x = value; } }
        public float Y { get => _y; set { _y = value; } }
        public float Z { get => _z; set { _z = value; } }

        // Color Mode Definitions
        public float R { get => _x; set { _x = value; } }
        public float G { get => _y; set { _y = value; } }
        public float B { get => _z; set { _z = value; } }

        public Vec3() { }
        public Vec3(float x, float y, float z) { _x = x; _y = y; _z = z; }

        /// <summary>
        /// Sum two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The sum</returns>
        public static Vec3 Sum(Vec3 a, Vec3 b)
        {
            return new Vec3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        }

        /// <summary>
        /// Subtract's two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The subtraction</returns>
        public static Vec3 Subtract(Vec3 a, Vec3 b)
        {
            return new Vec3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }

        /// <summary>
        /// Multiplie's two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The multiplication</returns>
        public static Vec3 Multiply(Vec3 a, Vec3 b)
        {
            return new Vec3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
        }

        /// <summary>
        /// Divide's to vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The divide result</returns>
        public static Vec3 Divide(Vec3 a, Vec3 b)
        {
            return new Vec3(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
        }

        public static Vec3 operator +(Vec3 a, Vec3 b)
        {
            return Sum(a, b);
        }

        public static Vec3 operator -(Vec3 a, Vec3 b)
        {
            return Subtract(a, b);
        }

        public static Vec3 operator *(Vec3 a, Vec3 b)
        {
            return Multiply(a, b);
        }

        public static Vec3 operator /(Vec3 a, Vec3 b)
        {
            return Divide(a, b);
        }

        public override string ToString()
        {
            return $"(x: {X}, y: {Y}, z: {Z})";
        }

        private float _x = 0.0f;
        private float _y = 0.0f;
        private float _z = 0.0f;
    }

    /// <summary>
    /// A rapresentation of 4 float values (x,y,z,w) (r,g,b,a)
    /// </summary>
    public class Vec4
    {
        // Spatial Mode Definitions
        public float X { get => _x; set { _x = value; } }
        public float Y { get => _y; set { _y = value; } }
        public float Z { get => _z; set { _z = value; } }
        public float W { get => _w; set { _w = value; } }

        // Color Mode Definitions
        public float R { get => _x; set { _x = value; } }
        public float G { get => _y; set { _y = value; } }
        public float B { get => _z; set { _z = value; } }
        public float A { get => _w; set { _w = value; } }

        public Vec4() { }
        public Vec4(float x, float y, float z, float w) { _x = x; _y = y; _z = z; _w = w; }

        /// <summary>
        /// Sum two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The sum</returns>
        public static Vec4 Sum(Vec4 a, Vec4 b)
        {
            return new Vec4(a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + b.W);
        }

        /// <summary>
        /// Subtract's two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The subtraction</returns>
        public static Vec4 Subtract(Vec4 a, Vec4 b)
        {
            return new Vec4(a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W);
        }

        /// <summary>
        /// Multiplie's two vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The multiplication</returns>
        public static Vec4 Multiply(Vec4 a, Vec4 b)
        {
            return new Vec4(a.X * b.X, a.Y * b.Y, a.Z * b.Z, a.W * b.W);
        }

        /// <summary>
        /// Divide's to vectors
        /// </summary>
        /// <param name="a">First</param>
        /// <param name="b">Second</param>
        /// <returns>The divide result</returns>
        public static Vec4 Divide(Vec4 a, Vec4 b)
        {
            return new Vec4(a.X / b.X, a.Y / b.Y, a.Z / b.Z, a.W / b.W);
        }

        public static Vec4 operator +(Vec4 a, Vec4 b)
        {
            return Sum(a, b);
        }

        public static Vec4 operator -(Vec4 a, Vec4 b)
        {
            return Subtract(a, b);
        }

        public static Vec4 operator *(Vec4 a, Vec4 b)
        {
            return Multiply(a, b);
        }

        public static Vec4 operator /(Vec4 a, Vec4 b)
        {
            return Divide(a, b);
        }

        public override string ToString()
        {
            return $"(x: {X}, y: {Y}, z: {Z}, w: {W})";
        }

        private float _x = 0.0f;
        private float _y = 0.0f;
        private float _z = 0.0f;
        private float _w = 0.0f;
    }
}