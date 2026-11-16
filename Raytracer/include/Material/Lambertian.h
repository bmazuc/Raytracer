#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "Material/Material.h"

/**
 * Represents a diffuse Lambertian material.
 */
class Lambertian : public Material
{
public:
	/**
	 * Scatters incoming rays in randomized directions over the
	 * surface hemisphere to approximate diffuse light reflection.
	 */
	Lambertian(const Color& inAlbedo = Color::white);

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	Color GetAlbedo() const { return albedo; }

protected:
	Color albedo;
};

#endif // RAYTRACER_LAMBERTIAN_H