#include "Material/Metal.h"
#include "Color.h"
#include "Maths/Vec3.h"
#include "Ray.h"
#include "Scene/Hittable.h"

Metal::Metal(const Color& inAlbedo, float inRoughness)
	: albedo(inAlbedo), roughness(inRoughness < 1 ? inRoughness : 1)
{
}

bool Metal::Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	Vec3 reflected = Vec3::Reflect(rayIn.direction, hitInfo.normal);
	reflected = reflected.GetNormal() + (roughness * Vec3::RandomUnitVector());

	scattered = Ray(hitInfo.point, reflected);
	attenuation = albedo;
	
	return (Vec3::Dot(scattered.direction, hitInfo.normal) > 0);
}