#ifndef RAYTRACER_SKY_H
#define RAYTRACER_SKY_H

struct Color;
struct Ray;

class Sky
{
public:
	~Sky() = default;

	virtual Color GetPixelColor(const Ray& ray) const = 0;
};

#endif // RAYTRACER_SKY_H