#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Color.h"

struct Ray;
struct HitInfo;

/**
 * Defines how an object is rendered.
 */
class Material
{
public:
	virtual ~Material() = default;

	/**
	 * Simulate the behavior
     * of light when it interacts with a surface.
	 */
	virtual bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const = 0;
};

#endif // RAYTRACER_MATERIAL_H