#include "Raytracer.h"
#include "Scene/Scene.h"

Raytracer::Raytracer(const CameraConfiguration& cameraConfig, const RendererConfig& rendererConfig)
	: camera(cameraConfig), renderer(rendererConfig)
{
}

void Raytracer::SetScene(std::unique_ptr<Scene> newScene)
{
    scene = std::move(newScene);
}

void Raytracer::Render(std::string fileName)
{
    if (!scene)
    {
        return;
    }

    renderer.Render(camera, *scene, fileName);
}