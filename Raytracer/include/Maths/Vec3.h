#ifndef RAYTRACER_VEC3_H
#define	RAYTRACER_VEC3_H

#include <iostream>

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
	Vec3 operator/(const Vec3& rhs);
	Vec3 operator/(float f) const;

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(const Vec3& rhs);
	Vec3& operator*=(float f);
	Vec3& operator/=(const Vec3& rhs);
	Vec3& operator/=(float f);

	float Length() const;
	float LengthSquared() const;

	Vec3 GetNormal() const;
	void Normalize();

	static float Dot(const Vec3& lhs, const Vec3& rhs);
	static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);

	static Vec3 Random();
	static Vec3 Random(float min, float max);

	static Vec3 RandomUnitVector();
	static Vec3 RandomOnHemisphere(const Vec3& normal);
	static Vec3 RandomInUnitDisk();

	static Vec3 Reflect(const Vec3& incident, const Vec3& normal);

	/**
	 * @param eta : ratio of indices of refraction
	 */
	static Vec3 Refract(const Vec3& incident, const Vec3& normal, float eta);

	// return true if the vector is close to zero in all dimensions.
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