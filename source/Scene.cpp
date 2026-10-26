#include "Scene.h"
#include "Camera.h"

Scene::Scene()
{
	camera = new Camera();
}

void Scene::Add(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

void Scene::Clear()
{
	objects.clear();
}

bool Scene::Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const
{
	HitInfo tempHitInfo;
	bool hasHitAnything = false;
	float closestSoFar = t.Max();

	for (const std::shared_ptr<Hittable>& object : objects)
	{
		if (object && object->Hit(ray, Interval(t.Min(), closestSoFar), tempHitInfo))
		{
			hasHitAnything = true;
			closestSoFar = tempHitInfo.t;
			hitInfo = tempHitInfo;
		}
	}

	return hasHitAnything;
}

Scene::~Scene()
{
	Clear();

	if (camera)
	{
		delete camera;
		camera = nullptr;
	}
}