#include "Ray.h"

Ray::Ray(const Vec3& inOrigin, const Vec3& inDirection)
	: origin(inOrigin), direction(inDirection)
{
}

Vec3 Ray::At(float t) const
{
	return origin + direction * t;
}