#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H

#include "Material/Material.h"

/**
 * Represents a transparent dielectric material.
 */
class Dielectric : public Material
{
public:
	Dielectric(float inRefractionIndex);

	/**
	 * Simulates light reflection and refraction using the material's
     * refractive index and the Schlick approximation.
	 */
	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	float GetRefractionIndex() const { return refractionIndex; }

private:
	float Reflectance(float cos, float eta) const;

	// Refractive index in vacuum or air, or the ratio of the material's refractive index over the refractive index of the enclosing media
	float refractionIndex;
};

#endif // RAYTRACER_DIELECTRIC_H