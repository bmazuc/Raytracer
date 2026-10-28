#ifndef __LAMBERTIAN_H_INCLUDED__
#define __LAMBERTIAN_H_INCLUDED__

#include "Material/Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Color& inAlbedo = Color::white);

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

protected:
	Color albedo;
};

#endif // __LAMBERTIAN_H_INCLUDED__