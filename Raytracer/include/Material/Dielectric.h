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
	 * Computes reflection and refraction for a transparent material.
	 *
	 * Determines whether the incoming ray is reflected or refracted
	 * according to the refractive index and the angle of incidence.
	 *
	 * Uses the Schlick approximation to estimate reflectance.
	 *
	 * @param rayIn Incoming ray.
	 * @param hitInfo Surface intersection information.
	 * @param attenuation Output color attenuation.
	 * @param scattered Output reflected or refracted ray.
	 * @return True if a scattered ray is generated.
	 */
	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	float GetRefractionIndex() const { return refractionIndex; }

private:
	/**
	 *  Estimates the reflectance of a dielectric surface.
	 *
	 * Uses the Schlick approximation to calculate the probability
	 * of reflection according to the incidence angle and refractive index.
	 *
	 * @param cos Cosine of the angle between the incoming ray
	 * and the surface normal.
	 * @param eta Ratio of refractive indices.
	 * @return Estimated reflection coefficient.
	 */
	float Reflectance(float cos, float eta) const;

	// Refractive index in vacuum or air, or the ratio of the material's refractive index over the refractive index of the enclosing media
	float refractionIndex;
};

#endif // RAYTRACER_DIELECTRIC_H