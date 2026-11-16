#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "Maths/Vec3.h"
#include "Maths/Interval.h"

struct Ray;
class Material;

/**
 * Stores information about the intersection between
 * a ray and a hittable object.
 */
struct HitInfo
{
public:
	// World-space position of the intersection
	Vec3 point;
	// Surface normal oriented against the incoming ray
	Vec3 normal;
	// Material assigned to the intersected object
	std::shared_ptr<Material> material;
	// Ray parameter at the intersection point
	float t = 0.0f;
	// True when the ray hits the outward-facing side of the surface
	bool frontFace = false;
};

/**
 * Abstraction for objects that can be intersected by a ray.
 */
class Hittable
{
public:
	virtual ~Hittable() = default;

	/**
	 * Determines whether a ray intersects the object.
	 *
	 * Implemented by concrete hittable objects to perform
	 * geometry-specific intersection tests.
	 *
	 * @param ray Ray being tested.
	 * @param t Valid interval for the intersection distance.
	 * @param hitInfo Output structure populated with intersection details.
	 * @return True if a valid intersection is found, false otherwise.
	 */
	virtual bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const = 0;

protected:
	/**
	 * Sets the intersection normal according to the ray direction.
	 *
	 * Determines whether the ray hits the front or back face of a surface
	 * and adjusts the normal to always oppose the incoming ray.
	 *
	 * @param ray Incoming ray.
	 * @param outwardNormal Normal pointing outward from the surface.
	 * @param hitInfo Intersection information to update.
	 */
	void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal, HitInfo& hitInfo) const;
};

#endif // RAYTRACER_HITTABLE_H