#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Maths/Vec3.h"

/**
 * Represents a ray defined by an origin and a direction.
 */
struct Ray
{
public:

	Ray() = default;
	Ray(const Vec3& inOrigin, const Vec3& inDirection);

	/**
	 * Evaluates a position along the ray.
	 * 
	 * @param t Distance parameter along the ray.
	 * @return Position corresponding to the given parameter.
	 */
	Vec3 At(float t) const;

	Vec3 origin;
	Vec3 direction;
};

#endif // RAYTRACER_RAY_H