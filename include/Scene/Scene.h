#ifndef __HITTABLE_LIST_H_INCLUDED__
#define __HITTABLE_LIST_H_INCLUDED__

#include "Hittable.h"

#include <memory>
#include <vector>

class Camera;
struct Color;
class Sky;

class Scene
{
public:
	~Scene();

	void SetSky(Sky* newSky);

	void Add(std::shared_ptr<Hittable> object);
	void Clear();

	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const;

	Color GetPixelColor(const Ray& ray, int depth) const;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
	Sky* sky;
};

#endif // __HITTABLE_LIST_H_INCLUDED__