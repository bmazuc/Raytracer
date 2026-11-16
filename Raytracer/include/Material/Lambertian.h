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
	 * Computes diffuse light scattering using a Lambertian model.
	 * 
	 * @param rayIn Incoming ray.
	 * @param hitInfo Surface intersection information.
	 * @param attenuation Output diffuse color attenuation.
	 * @param scattered Output scattered ray.
	 * @return True if a scattered ray is generated.
	 */
	Lambertian(const Color& inAlbedo = Color::white);

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	Color GetAlbedo() const { return albedo; }

protected:
	// Base color tint applied to reflected rays
	Color albedo;
};

#endif // RAYTRACER_LAMBERTIAN_H