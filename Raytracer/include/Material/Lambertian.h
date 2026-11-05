#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "Material/Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Color& inAlbedo = Color::white);

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

protected:
	Color albedo;
};

#endif // RAYTRACER_LAMBERTIAN_H