#ifndef RAYTRACER_SCENE_SERIALIZER_H
#define RAYTRACER_SCENE_SERIALIZER_H

#include <nlohmann/json.hpp>
#include <string>
#include <memory>

class Camera;
class Scene;
class Raytracer;

struct CameraConfiguration;

/**
 * Handles serialization and deserialization of complete scenes.
 *
 * Saves and restores camera settings, scene objects and associated
 * scene data using JSON files.
 */
class SceneSerializer
{
public:
	/**
	 * Serializes the camera configuration and scene contents
	 * into a JSON representation.
	 *
	 * @param filepath Destination JSON file path.
	 * @param camera Camera configuration to save.
	 * @param scene Scene to serialize.
	 */
	static void Save(const std::string& filepath, const Camera& camera, const Scene& scene);
	/**
	 * Deserializes the stored data and restores the camera
	 * and scene objects.
	 *
	 * @param filepath Source JSON file path.
	 * @param camera Camera to configure.
	 * @param scene Scene pointer to populate.
	 */
	static void Load(const std::string& filepath, Camera& camera, std::unique_ptr<Scene>& scene);

	/**
	 * Serializes the camera and scene managed by the ray tracer.
	 *
	 * @param filepath Destination JSON file path.
	 * @param raytracer Ray tracing instance to serialize.
	 */
	static void Save(const std::string& filepath, const std::unique_ptr<Raytracer>& raytracer);
	/**
	 * Reconstructs the ray tracer and its associated scene
	 * from the serialized representation.
	 *
	 * @param filepath Source JSON file path.
	 * @param raytracer Ray tracer instance to initialize.
	 */
	static void Load(const std::string& filepath, std::unique_ptr<Raytracer>& raytracer);

private:
	/**
	 *  Converts a camera configuration into its JSON representation.
	 *
	 * @param config Camera configuration to serialize.
	 * @return JSON object representing the camera configuration.
	 */
	static nlohmann::json CameraToJson(const CameraConfiguration& config);
	/**
	 * Reconstructs a camera configuration from JSON data.
	 *
	 * @param json JSON object containing camera parameters.
	 * @return Deserialized camera configuration.
	 */
	static CameraConfiguration CameraFromJson(const nlohmann::json& json);
};

#endif // RAYTRACER_SCENE_SERIALIZER_H