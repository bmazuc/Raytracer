#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(Vec3 inPosition, float inRadius, std::shared_ptr<Material> inMaterial)
	: position(inPosition), radius(inRadius), material(inMaterial)
{
}

bool Sphere::Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const
{
	// Vector from the ray origin to the sphere position.
	Vec3 oc = position - ray.origin;

	/**
	 * Expand the sphere equation along the ray into a quadratic equation:
	 * a*t² + b*t + c = 0.
	 */
	float a = ray.direction.LengthSquared();
	float h = Vec3::Dot(ray.direction, oc);
	float c = oc.LengthSquared() - radius * radius;

	// The discriminant determines whether the ray intersects the sphere.
	float discriminant = h*h - a*c;
	
	if (discriminant < 0)
	{
		return false;
	}

	float sqrtd = std::sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	float root = (h - sqrtd) / a;
	if (!t.Surrounds(root))
	{
		root = (h + sqrtd) / a;
		if (!t.Surrounds(root))
		{
			return false;
		}
	}

	hitInfo.t = root;
	hitInfo.point = ray.At(hitInfo.t);
	Vec3 outwardNormal = ((hitInfo.point - position) / radius).GetNormal();
	SetFaceNormal(ray, outwardNormal, hitInfo);
	hitInfo.material = material;

	return true;
}