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

	/**
	 * Replaces the current sky model.
	 * Transfers ownership of the provided sky to the scene.
	 *
	 * @param newSky Sky model to assign to the scene.
	 */
	void SetSky(std::unique_ptr<Sky> newSky);

	/**
	 * Adds a geometric object to the scene
	 * and stores it in the scene's geometry collection.
	 *
	 * @param object Object to add to the scene.
	 */
	void Add(std::shared_ptr<Hittable> object);
	/**
	 * Removes all geometric objects from the scene.
	 */
	void Clear();

	const std::vector<std::shared_ptr<Hittable>>& GetObjects() const { return objects; }
	std::vector<std::shared_ptr<Hittable>>&GetObjects() { return objects; }

	/**
	 * Finds the closest intersection between a ray and scene geometry.
	 *
	 * Tests the ray against all hittable objects and updates the
	 * intersection information with the closest valid hit.
	 *
	 * @param ray Ray being tested.
	 * @param t Valid interval for the intersection distance.
	 * @param hitInfo Output structure containing the closest intersection.
	 * @return True if an object is hit within the specified interval.
	 */
	bool Hit(const Ray& ray, Interval t, HitInfo& hitInfo) const;

	/**
	 * Evaluates the color produced by a ray interacting with the scene.
	 *
	 * Recursively evaluates ray-material interactions while respecting
	 * the maximum recursion depth.
	 *
	 * Returns the scene background color when no object is intersected.
	 *
	 * @param ray Ray used to evaluate the scene.
	 * @param depth Remaining recursion depth.
	 * @return Color contribution associated with the ray.
	 */
	Color GetPixelColor(const Ray& ray, int depth) const;

private:
	// Geometric objects tested when tracing scene rays
	std::vector<std::shared_ptr<Hittable>> objects;
	// Background model used when a ray misses all scene objects
	std::unique_ptr<Sky> sky;
};

#endif // RAYTRACER_SCENE_H