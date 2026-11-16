#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"

struct Ray;
class Material;

/**
 * Represents a spherical object in a 3D scene.
 */
class Sphere : public Hittable
{
public:
	Sphere(Vec3 inPosition = Vec3(0, 0, 0), float inRadius = 0.0f, std::shared_ptr<Material> inMaterial = nullptr);

	void SetPosition(Vec3 inPosition) { position = inPosition; }
	void SetRadius(float inRadius) { radius = inRadius; }

	Vec3 GetCenter() const { return position; }
	float GetRadius() const { return radius; }
	std::shared_ptr<Material> GetMaterial() { return material; }
	const std::shared_ptr<Material> GetMaterial() const { return material; }

	/**
	 * Checks whether a ray intersects a sphere.
	 */
	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const override;

private:
	Vec3 position;
	float radius;

	std::shared_ptr<Material> material;
};

#endif // RAYTRACER_SPHERE_H