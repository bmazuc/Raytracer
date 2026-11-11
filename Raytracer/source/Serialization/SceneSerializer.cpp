#include "Serialization/SceneSerializer.h"
#include "Serialization/JsonTypes.h"
#include "Serialization/SkySerializer.h"
#include "Serialization/ObjectSerializer.h"
#include "Camera.h"
#include "Scene/Scene.h"
#include "Raytracer.h"
#include "Material/Lambertian.h"

#include <fstream>

void SceneSerializer::Save(const std::string& filepath, const std::unique_ptr<Raytracer>& raytracer)
{
    Scene* scene = raytracer->GetScene();
    if (scene)
    {
        Save(filepath, *raytracer->GetCamera(), *scene);
    }
}

void SceneSerializer::Load(const std::string& filepath, std::unique_ptr<Raytracer>& raytracer)
{
    std::unique_ptr<Scene> loadedScene;
    Load(filepath, *raytracer->GetCamera(), loadedScene);
    raytracer->SetScene(std::move(loadedScene));
}

void SceneSerializer::Save(const std::string& filepath, const Camera& camera, const Scene& scene)
{
    nlohmann::json json;

    json["version"] = 1;
    json["camera"] = CameraToJson(camera.GetConfiguration());

    json["scene"]["sky"] = SkySerializer::SkyToJson(scene.GetSky());

    json["scene"]["objects"] = nlohmann::json::array();

    for (const auto& object : scene.GetObjects())
    {
        json["scene"]["objects"].push_back(ObjectSerializer::ObjectToJson(object));
    }

    std::ofstream file(filepath);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filepath);

    file << json.dump(4);
}

void SceneSerializer::Load(const std::string& filepath, Camera& camera, std::unique_ptr<Scene>& scene)
{
    std::ifstream file(filepath);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filepath);

    nlohmann::json json;
    file >> json;

    // Check file version
    if (json.at("version").get<int>() != 1)
        throw std::runtime_error("Unsupported scene file version");

    // Reconstruct camera configuration
    CameraConfiguration cameraConfig =
        CameraFromJson(json.at("camera"));

    // Reconstruct scene
    auto loadedScene = std::make_unique<Scene>();

    const nlohmann::json& sceneJson = json.at("scene");

    loadedScene->SetSky(SkySerializer::SkyFromJson(sceneJson.at("sky")));

    for (const auto& objectJson : sceneJson.at("objects"))
    {
        loadedScene->Add(ObjectSerializer::ObjectFromJson(objectJson));
    }

    // Apply everything only after successful reconstruction
    camera.SetConfiguration(cameraConfig);
    scene = std::move(loadedScene);
}

nlohmann::json SceneSerializer::CameraToJson(const CameraConfiguration& config)
{
    return {
        {"imageWidth", config.imageWidth},
        {"aspectRatio", config.aspectRatio},
        {"fov", config.fov},

        {"position", config.position},
        {"lookAt", config.lookAt},
        {"vUp", config.vUp},

        {"samplesPerPixel", config.samplesPerPixel},
        {"maxDepth", config.maxDepth},

        {"defocusAngle", config.defocusAngle},
        {"focusDistance", config.focusDistance}
    };
}

CameraConfiguration SceneSerializer::CameraFromJson(const nlohmann::json& json)
{
    CameraConfiguration config;

    config.imageWidth = json.at("imageWidth").get<size_t>();
    config.aspectRatio = json.at("aspectRatio").get<float>();
    config.fov = json.at("fov").get<float>();

    config.position = json.at("position").get<Vec3>();
    config.lookAt = json.at("lookAt").get<Vec3>();
    config.vUp = json.at("vUp").get<Vec3>();

    config.samplesPerPixel = json.at("samplesPerPixel").get<unsigned int>();
    config.maxDepth = json.at("maxDepth").get<unsigned int>();

    config.defocusAngle = json.at("defocusAngle").get<float>();
    config.focusDistance = json.at("focusDistance").get<float>();

    return config;
}