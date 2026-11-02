#include "Raytracer.h"
#include "Scene/Scene.h"

Raytracer::Raytracer(const CameraConfiguration& config)
	: camera(config)
{
}

void Raytracer::SetScene(std::unique_ptr<Scene> newScene)
{
    scene = std::move(newScene);
}

void Raytracer::Render()
{
    if (!scene)
    {
        return;
    }

    PPMWriter writer(std::cout);

    renderer.Render(camera, *scene, writer);
}