#include "Material/Dielectric.h"
#include "Hittable.h"
#include "Ray.h"
#include "Maths/Maths.h"

Dielectric::Dielectric(float inRefractionIndex)
	: refractionIndex(inRefractionIndex)
{
}

bool Dielectric::Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	attenuation = Color::white;

	float eta = hitInfo.frontFace ? (1.0f / refractionIndex) : refractionIndex;

	Vec3 unitDirection = rayIn.direction.GetNormal();

	float cosTheta = std::fmin(Vec3::Dot(-unitDirection, hitInfo.normal), 1.0f);
	float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

	bool canRefract = eta * sinTheta <= 1.0;

	Vec3 direction;

	if (canRefract && Reflectance(cosTheta, eta) <= maths::Random())
	{
		direction = Vec3::Refract(unitDirection, hitInfo.normal, eta);
	}
	else
	{
		direction = Vec3::Reflect(unitDirection, hitInfo.normal);
	}

	scattered = Ray(hitInfo.point, direction);
	return true;
}

float Dielectric::Reflectance(float cos, float eta) const
{
	// Use schlick's approximation for reflectance.
	float r0 = (1.0f - eta) / (1.0f + eta);
	r0 = r0 * r0;
	return r0 + (1 - r0) * std::pow((1 - cos), 5.0f);
}