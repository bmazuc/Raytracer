#include "Scene/Sky/GradientSky.h"
#include "Ray.h"

GradientSky::GradientSky(Color inHorizonColor, Color inZenithColor)
	: horizonColor(inHorizonColor), zenithColor(inZenithColor)
{
}

Color GradientSky::GetPixelColor(const Ray& ray) const
{
	Vec3 normalizeDirection = ray.direction.GetNormal();
	float t = 0.5f * (normalizeDirection.y + 1.0f);
	return Color::Lerp(horizonColor, zenithColor, t);
}