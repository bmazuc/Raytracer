#ifndef __METAL_H_INCLUDED__
#define __METAL_H_INCLUDED__

#include "Material/Material.h"

class Metal : public Material
{
public:
	Metal(const Color& inAlbedo = Color::white, float inRoughness = 1.0f);
	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
	float roughness;
};

#endif // __METAL_H_INCLUDED__