#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Maths/Vec3.h"

struct Ray
{
public:

	Ray() = default;
	Ray(const Vec3& inOrigin, const Vec3& inDirection);

	Vec3 At(float t) const;

	Vec3 origin;
	Vec3 direction;
};

#endif // RAYTRACER_RAY_H