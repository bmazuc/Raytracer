#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Hittable.h"
#include "Scene/Sky/Sky.h"

#include <memory>
#include <vector>

class Camera;
struct Color;

class Scene
{
public:
	void SetSky(std::unique_ptr<Sky> newSky);

	void Add(std::shared_ptr<Hittable> object);
	void Clear();

	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const;

	Color GetPixelColor(const Ray& ray, int depth) const;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
	std::unique_ptr<Sky> sky;
};

#endif // RAYTRACER_SCENE_H