#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "Material/Material.h"

class Metal : public Material
{
public:
	Metal(const Color& inAlbedo = Color::white, float inRoughness = 1.0f);
	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	Color GetAlbedo() const { return albedo; }
	float GetRoughness() const { return roughness; }

private:
	Color albedo;
	float roughness;
};

#endif // RAYTRACER_METAL_H