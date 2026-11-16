#ifndef RAYTRACER_GRADIENT_SKY_H
#define RAYTRACER_GRADIENT_SKY_H

#include "Scene/Sky/Sky.h"
#include "Color.h"

/**
 * Represents a gradient-based sky background.
 */
class GradientSky : public Sky
{
public:
	GradientSky(Color inHorizonColor, Color inZenithColor);

	/**
	 * Computes the background color using a vertical gradient.
	 *
	 * Interpolates between the horizon and zenith colors according
	 * to the vertical component of the ray direction.
	 *
	 * @param ray Ray used to determine the gradient position.
	 * @return Interpolated background color.
	 */
	Color GetPixelColor(const Ray& ray) const override;

	Color GetHorizonColor() const { return horizonColor; }
	Color GetZenithColor() const { return zenithColor; }

	void SetHorizonColor(Color inHorizonColor) { horizonColor = inHorizonColor; }
	void SetZenithColor(Color inZenithColor) { zenithColor = inZenithColor; }

private:
	// Gradient color near the horizon
	Color horizonColor;
	// Gradient color toward the zenith
	Color zenithColor;
};

#endif // RAYTRACER_GRADIENT_SKY_H