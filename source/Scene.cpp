#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Maths/Maths.h"

void Scene::Create()
{
	if (!isCreated)
	{
		InternalCreate();
		isCreated = true;
	}
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

Color Scene::GetPixelColor(const Ray& ray) const
{
	HitInfo hitInfo;
	if (Hit(ray, Interval(0, maths::infinity), hitInfo))
	{
		return 0.5f * (
			Color(hitInfo.normal.x,
				hitInfo.normal.y,
				hitInfo.normal.z)
			+ Color::white);
	}

	Vec3 normalizeDirection = ray.direction.GetNormal();
	float a = 0.5f * (normalizeDirection.y + 1.0f);
	return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}

Scene::~Scene()
{
	Clear();
}