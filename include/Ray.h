#ifndef __RAY_H_INCLUDED__
#define __RAY_H_INCLUDED__

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

#endif // __RAY_H_INCLUDED__