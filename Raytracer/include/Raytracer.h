#ifndef __RAYTRACER_H_INCLUDED__
#define __RAYTRACER_H_INCLUDED__

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

    void Render(std::string fileName);

private:
    Renderer renderer;
    Camera camera;
    std::unique_ptr<Scene> scene;
};

#endif // __RAYTRACER_H_INCLUDED__