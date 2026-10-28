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

Color Scene::GetPixelColor(const Ray& ray, int depth) const
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return Color(0.0f, 0.0f, 0.0f);

	HitInfo hitInfo;
	if (Hit(ray, Interval(0.001f, maths::infinity), hitInfo))
	{
		Vec3 direction = hitInfo.normal + Vec3::RandomUnitVector();//Vec3::RandomOnHemisphere(hitInfo.normal);
		return 0.5f * GetPixelColor(Ray(hitInfo.point, direction), depth-1);
	}

	Vec3 normalizeDirection = ray.direction.GetNormal();
	float a = 0.5f * (normalizeDirection.y + 1.0f);
	return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}

Scene::~Scene()
{
	Clear();
}