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
	Vec3 point;
	Vec3 normal;
	std::shared_ptr<Material> material;
	float t;
	bool frontFace;
};

/**
 * Abstraction for objects that can be intersected by a ray.
 */
class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const = 0;

protected:
	void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal, HitInfo& hitInfo) const;
};

#endif // RAYTRACER_HITTABLE_H