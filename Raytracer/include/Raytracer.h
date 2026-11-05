#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "Renderer.h"
#include "Camera.h"
#include "Image/PPMWriter.h"

#include <memory>

class Scene;
struct CameraConfiguration;
struct RendererConfig;

class Raytracer
{
public:
    Raytracer(const CameraConfiguration& cameraConfig, const RendererConfig& rendererConfig);

    void SetScene(std::unique_ptr<Scene> newScene);

    void RenderToFile(std::string fileName);

private:
    Renderer renderer;
    Camera camera;
    std::unique_ptr<Scene> scene;
};

#endif // RAYTRACER_RAYTRACER_H