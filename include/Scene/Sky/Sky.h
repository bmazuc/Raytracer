#ifndef __SKY_H_INCLUDED__
#define __SKY_H_INCLUDED__

struct Color;
struct Ray;

class Sky
{
public:
	~Sky() = default;

	virtual Color GetPixelColor(const Ray& ray) const = 0;
};

#endif // __SKY_H_INCLUDED__