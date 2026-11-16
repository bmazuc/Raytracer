#ifndef RAYTRACER_SKY_H
#define RAYTRACER_SKY_H

struct Color;
struct Ray;

/**
 * Abstraction for scene background.
 */
class Sky
{
public:
	virtual ~Sky() = default;

	/**
	 * Computes the background color associated with a ray direction.
	 *
	 * Implemented by concrete sky models to define their own
	 * background color evaluation.
	 *
	 * @param ray Ray used to determine the background color.
	 * @return Background color associated with the ray.
	 */
	virtual Color GetPixelColor(const Ray& ray) const = 0;
};

#endif // RAYTRACER_SKY_H