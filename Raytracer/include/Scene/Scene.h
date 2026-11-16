#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Hittable.h"
#include "Scene/Sky/Sky.h"

#include <memory>
#include <vector>

class Camera;
struct Color;

/**
 * Represents a 3D scene containing geometric objects
 * and a background sky.
 * 
 * Manages scene objects and provides ray intersection queries
 * and pixel color evaluation through recursive ray tracing.
 */
class Scene
{
public:
	Sky* GetSky() { return sky.get(); }
	const Sky* GetSky() const { return sky.get(); }

	void SetSky(std::unique_ptr<Sky> newSky);

	void Add(std::shared_ptr<Hittable> object);
	void Clear();

	const std::vector<std::shared_ptr<Hittable>>& GetObjects() const { return objects; }
	std::vector<std::shared_ptr<Hittable>>&GetObjects() { return objects; }

	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const;

	Color GetPixelColor(const Ray& ray, int depth) const;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
	std::unique_ptr<Sky> sky;
};

#endif // RAYTRACER_SCENE_H