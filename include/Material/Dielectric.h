#ifndef __DIELECTRIC_H_INCLUDED__
#define __DIELECTRIC_H_INCLUDED__

#include "Material/Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float inRefractionIndex);

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

private:
	float Reflectance(float cos, float eta) const;

	// Refractive index in vacuum or air, or the ratio of the material's refractive index over
	// the refractive index of the enclosing media
	float refractionIndex;
};

#endif // __DIELECTRIC_H_INCLUDED__