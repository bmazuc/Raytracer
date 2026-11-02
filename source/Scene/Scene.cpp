#include "Scene/Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Maths/Maths.h"
#include "Material/Material.h"
#include "Scene/Sky/Sky.h"

void Scene::Add(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

void Scene::Clear()
{
	objects.clear();
	if (sky)
	{
		delete sky;
		sky = nullptr;
	}
}

void Scene::SetSky(Sky* newSky) 
{ 
	if (sky)
	{
		delete sky;
		sky = nullptr;
	}
	sky = newSky; 
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
	if (depth > 0)
	{
		HitInfo hitInfo;
		if (Hit(ray, Interval(0.001f, maths::infinity), hitInfo))
		{
			Ray scattered;
			Color attenuation;
			if (hitInfo.material->Scatter(ray, hitInfo, attenuation, scattered))
			{
				return attenuation * GetPixelColor(scattered, depth - 1);
			}
		}
		else if (sky)
		{
			return sky->GetPixelColor(ray);
		}
	}

	return Color(0.0f, 0.0f, 0.0f);
}

Scene::~Scene()
{
	Clear();
}