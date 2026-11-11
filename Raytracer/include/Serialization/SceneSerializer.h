#ifndef RAYTRACER_SCENE_SERIALIZER_H
#define RAYTRACER_SCENE_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <string>
#include <memory>

class Camera;
class Scene;
class Raytracer;

struct CameraConfiguration;

class SceneSerializer
{
public:
	static void Save(const std::string& filepath, const Camera& camera, const Scene& scene);
	static void Load(const std::string& filepath, Camera& camera, std::unique_ptr<Scene>& scene);

	static void Save(const std::string& filepath, const std::unique_ptr<Raytracer>& raytracer);
	static void Load(const std::string& filepath, std::unique_ptr<Raytracer>& raytracer);

private:
	static nlohmann::json CameraToJson(const CameraConfiguration& config);
	static CameraConfiguration CameraFromJson(const nlohmann::json& json);
};

#endif // RAYTRACER_SCENE_SERIALIZER_H