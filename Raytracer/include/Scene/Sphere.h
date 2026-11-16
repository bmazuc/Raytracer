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
	 * Computes the intersection between a ray and the sphere.
	 *
	 * Solves the ray-sphere intersection equation and stores
	 * the closest valid intersection within the specified interval.
	 *
	 * @param ray Ray being tested.
	 * @param t Valid interval for the intersection distance.
	 * @param hitInfo Output structure containing the intersection data.
	 * @return True if the ray intersects the sphere within the interval.
	 */
	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const override;

private:
	// World-space center of the sphere
	Vec3 position;
	// Sphere radius in world-space units
	float radius;

	// Material used when a ray intersects the sphere
	std::shared_ptr<Material> material;
};

#endif // RAYTRACER_SPHERE_H