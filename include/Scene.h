#ifndef __HITTABLE_LIST_H_INCLUDED__
#define __HITTABLE_LIST_H_INCLUDED__

#include "Hittable.h"

#include <memory>
#include <vector>

class Camera;

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Create() {};

	Camera* GetCamera() { return camera; }
	const Camera* GetCamera() const { return camera; }

	void Add(std::shared_ptr<Hittable> object);
	void Clear();

	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const;

private:
	Camera* camera;

	std::vector<std::shared_ptr<Hittable>> objects;
};

#endif // __HITTABLE_LIST_H_INCLUDED__