#ifndef RAYTRACER_GRADIENT_SKY_H
#define RAYTRACER_GRADIENT_SKY_H

#include "Scene/Sky/Sky.h"
#include "Color.h"

class GradientSky : public Sky
{
public:
	GradientSky(Color inHorizonColor, Color inZenithColor);

	Color GetPixelColor(const Ray& ray) const override;

	Color GetHorizonColor() const { return horizonColor; }
	Color GetZenithColor() const { return zenithColor; }

	void SetHorizonColor(Color inHorizonColor) { horizonColor = inHorizonColor; }
	void SetZenithColor(Color inZenithColor) { zenithColor = inZenithColor; }

private:
	Color horizonColor;
	Color zenithColor;
};

#endif // RAYTRACER_GRADIENT_SKY_H