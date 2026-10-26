#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(Vec3 inCenter, float inRadius, Color inColor)
	: center(inCenter), radius(inRadius), color(inColor)
{
}

bool Sphere::IsHit(const Ray& ray)
{
	// Vector from the ray origin to the sphere center.
	Vec3 oc = center - ray.origin;

	/**
	 * Expand the sphere equation along the ray into a quadratic equation:
	 * a*t² + b*t + c = 0.
	 */
	float a = Vec3::Dot(ray.direction, ray.direction);
	float b = -2.0f * Vec3::Dot(ray.direction, oc);
	float c = Vec3::Dot(oc, oc) - radius * radius;

	// The discriminant determines whether the ray intersects the sphere.
	float discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}