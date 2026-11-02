#ifndef __GRADIENT_SKY_H_INCLUDED__
#define __GRADIENT_SKY_H_INCLUDED__

#include "Scene/Sky/Sky.h"
#include "Color.h"

class GradientSky : public Sky
{
public:
	GradientSky(Color inHorizonColor, Color inZenithColor);

	Color GetPixelColor(const Ray& ray) const override;

	Color GetHorizonColor() { return horizonColor; }
	Color GetZenithColor() { return zenithColor; }

	void SetHorizonColor(Color inHorizonColor) { horizonColor = inHorizonColor; }
	void SetZenithColor(Color inZenithColor) { zenithColor = inZenithColor; }

private:
	Color horizonColor;
	Color zenithColor;
};

#endif // __GRADIENT_SKY_H_INCLUDED__