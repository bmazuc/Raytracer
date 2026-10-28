#include "Material/Lambertian.h"
#include "Hittable.h"
#include "Ray.h"
#include "Color.h"

Lambertian::Lambertian(const Color& inAlbedo)
	: albedo(inAlbedo)
{
}

bool Lambertian::Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	Vec3 scatterDirection = hitInfo.normal + Vec3::RandomUnitVector();
	
	// Catch degenerate scatter direction
	if (scatterDirection.IsNearZero())
	{
		scatterDirection = hitInfo.normal;
	}
	
	scattered = Ray(hitInfo.point, scatterDirection);
	attenuation = albedo;
	return true;
}