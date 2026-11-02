#ifndef __RAYTRACER_H_INCLUDED__
#define __RAYTRACER_H_INCLUDED__

#include "Renderer.h"
#include "Camera.h"
#include "PPMWriter.h"

#include <memory>

class Scene;
struct CameraConfiguration;

class Raytracer
{
public:
    Raytracer(const CameraConfiguration& config);

    void SetScene(std::unique_ptr<Scene> newScene);

    void Render();

private:
    Renderer renderer;
    Camera camera;
    std::unique_ptr<Scene> scene;
};

#endif // __RAYTRACER_H_INCLUDED__