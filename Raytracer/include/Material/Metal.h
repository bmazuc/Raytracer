#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "Material/Material.h"

/**
 * Represents a reflective metallic material.
 */
class Metal : public Material
{
public:
	Metal(const Color& inAlbedo = Color::white, float inRoughness = 1.0f);
	
	/**
	 *Computes reflective light scattering for a metallic surface.
	 *
	 * @param rayIn Incoming ray.
	 * @param hitInfo Surface intersection information.
	 * @param attenuation Output metallic color attenuation.
	 * @param scattered Output reflected ray.
	 * @return True if the resulting ray points above the surface.
	 */
	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	Color GetAlbedo() const { return albedo; }
	float GetRoughness() const { return roughness; }

private:
	// Base color tint applied to reflected rays
	Color albedo;
	// Amount of perturbation applied to the ideal reflection direction
	float roughness;
};

#endif // RAYTRACER_METAL_H