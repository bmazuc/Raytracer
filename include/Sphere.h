#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

#include "Hittable.h"
#include "Color.h"

struct Ray;

class Sphere : public Hittable
{
public:
	Sphere(Vec3 inCenter = Vec3(0, 0, 0), float inRadius = 0.0f, Color inColor = Color::white);

	void SetCenter(Vec3 inCenter) { center = inCenter; }
	void SetRadius(float inRadius) { radius = inRadius; }
	void SetColor(Color inColor) { color = inColor; }

	Vec3 GetCenter() const { return center; }
	float GetRadius() const { return radius; }
	Color GetColor() const { return color; }

	/**
	 * Checks whether a ray intersects a sphere.
	 */
	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const override;

private:
	Vec3 center;
	float radius;

	Color color;
};

#endif // __SPHERE_H_INCLUDED__