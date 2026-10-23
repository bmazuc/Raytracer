#include "Vec3.h"

Vec3::Vec3()
	: x(0), y(0), z(0)
{
}

Vec3::Vec3(float inX, float inY, float inZ)
	: x(inX), y(inY), z(inZ)
{
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(const Vec3& rhs) const
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator-(const Vec3& rhs) const
{
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3 Vec3::operator*(const Vec3& rhs) const
{
	return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vec3 Vec3::operator*(float f) const
{
	return Vec3(x * f, y * f, z * f);
}

Vec3 Vec3::operator/(const Vec3& rhs)
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator/(float f) const
{
	return Vec3(x / f, y / f, z / f);
}

Vec3& Vec3::operator+=(const Vec3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vec3& Vec3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vec3& Vec3::operator/=(const Vec3& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

Vec3& Vec3::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

float Vec3::Length() const
{
	return std::sqrt(LengthSquared());
}

float Vec3::LengthSquared() const
{
	return x * x + y * y + z * z;
}

Vec3 Vec3::GetNormal()
{
	return *this / Length();
}

void Vec3::Normalize()
{
	float length = Length();
	x *= length;
	y *= length;
	z *= length;
}

float Vec3::Dot(const Vec3& lhs, const Vec3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vec3 Vec3::Cross(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}