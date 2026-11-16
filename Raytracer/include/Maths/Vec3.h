#ifndef RAYTRACER_VEC3_H
#define	RAYTRACER_VEC3_H

#include <iostream>

/**
 * Representation of 3D vectors and points.
 */
struct Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float inX, float inY, float inZ);

	Vec3 operator-() const;
	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(const Vec3& rhs) const;
	Vec3 operator*(float f) const;
	Vec3 operator/(const Vec3& rhs) const;
	Vec3 operator/(float f) const;

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(const Vec3& rhs);
	Vec3& operator*=(float f);
	Vec3& operator/=(const Vec3& rhs);
	Vec3& operator/=(float f);

	/**
	 * Returns the Euclidean length of the vector.
	 *
	 * @return Square root of the sum of the squared components.
	 */
	float Length() const;
	/**
	 * Returns the squared length of the vector.
	 *
	 * Avoids the square root computation when only comparing lengths
	 * is required.
	 *
	 * @return Sum of the squared components.
	 */
	float LengthSquared() const;

	/**
	 * Returns a normalized copy of the vector.
	 *
	 * @return Unit-length vector in the same direction.
	 */
	Vec3 GetNormal() const;
	/**
	 * Normalize this vector.
	 */
	void Normalize();

	/**
	 * Computes the dot product of two vectors.
	 *
	 * @param lhs First vector.
	 * @param rhs Second vector.
	 * @return Scalar dot product.
	 */
	static float Dot(const Vec3& lhs, const Vec3& rhs);
	/**
	 * Computes the cross product of two vectors.
	 *
	 * @param lhs First vector.
	 * @param rhs Second vector.
	 * @return Vector perpendicular to both input vectors.
	 */
	static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);

	/**
	 * Generates a random vector with components in [0, 1).
	 */
	static Vec3 Random();
	/**
	 * Generates a random vector with components in the given range.
	 *
	 * @param min Minimum component value.
	 * @param max Maximum component value.
	 */
	static Vec3 Random(float min, float max);

	/**
	 * Generates a random unit vector uniformly distributed
	 * over the unit sphere.
	 *
	 * @return Random normalized direction.
	 */
	static Vec3 RandomUnitVector();
	/**
	 * Generates a random direction in the hemisphere
	 * oriented around the provided normal.
	 *
	 * @param normal Reference hemisphere orientation.
	 * @return Random direction within the hemisphere.
	 */
	static Vec3 RandomOnHemisphere(const Vec3& normal);
	/**
	 * Generates a random point inside the unit disk in the XY plane.
	 *
	 * @return Random point within the unit disk.
	 */
	static Vec3 RandomInUnitDisk();

	/**
	 * Computes the reflection of an incident vector.
	 *
	 * @param incident Incoming direction.
	 * @param normal Surface normal.
	 * @return Reflected direction.
	 */
	static Vec3 Reflect(const Vec3& incident, const Vec3& normal);

	/**
	 * Computes the refraction of an incident vector using Snell's law.
	 *
	 * @param incident Incoming direction.
	 * @param normal Surface normal.
	 * @param eta Ratio of refractive indices.
	 * @return Refracted direction.
	 */
	static Vec3 Refract(const Vec3& incident, const Vec3& normal, float eta);

	/**
	 * Checks whether all vector components are close to zero.
	 * 
	 * @return True if all components are sufficiently close to zero.
	 */
	bool IsNearZero() const;
};

inline std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
	return os << vec.x << ' ' << vec.y << ' ' << vec.z;
}

inline Vec3 operator*(float f, const Vec3& rhs)
{
	return rhs * f;
}

inline Vec3 operator/(float f, const Vec3& rhs)
{
	return rhs / f;
}

#endif // RAYTRACER_VEC3_H