#ifndef __VEC3_H_INCLUDED__
#define	__VEC3_H_INCLUDED__

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

	Vec3 GetNormal();
	void Normalize();

	static float Dot(const Vec3& lhs, const Vec3& rhs);
	static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);
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

#endif // __VEC3_H_INCLUDED__