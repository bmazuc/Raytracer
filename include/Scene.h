#ifndef __HITTABLE_LIST_H_INCLUDED__
#define __HITTABLE_LIST_H_INCLUDED__

#include "Hittable.h"

#include <memory>
#include <vector>

class Camera;
struct Color;

class Scene
{
public:
	~Scene();

	void Create();

	void Add(std::shared_ptr<Hittable> object);
	void Clear();

	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const;

	Color GetPixelColor(const Ray& ray) const;

protected:
	virtual void InternalCreate() {}

private:
	bool isCreated = false;

	std::vector<std::shared_ptr<Hittable>> objects;
};

#endif // __HITTABLE_LIST_H_INCLUDED__