#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "Renderer.h"
#include "Camera.h"
#include "Image/ImageBuffer.h"

#include <memory>

class Scene;
struct CameraConfiguration;
struct RendererConfig;

struct OutputConfig
{
public:
    std::string directory;
    std::string filename;

    std::string GetPath() { return directory + '/' + filename; }
};

class Raytracer
{
public:
    Raytracer();
    Raytracer(const CameraConfiguration& cameraConfig, const RendererConfig& rendererConfig);

    Camera* GetCamera() { return &camera; }
    const Camera* GetCamera() const { return &camera; }

    Renderer* GetRenderer() { return &renderer; }
    const Renderer* GetRenderer() const { return &renderer; }

    ImageBuffer& GetImageBuffer() { return imageBuffer; }
    const ImageBuffer& GetImageBuffer() const { return imageBuffer; }

    void SetOutputConfig(const OutputConfig& inOutputConfig) { outputConfig = inOutputConfig; }
    void SetScene(std::unique_ptr<Scene> newScene);

    void RenderToFile(const ProgressCallback& callback, const std::atomic_bool& cancelRequested);

private:
    Renderer renderer;
    Camera camera;

    ImageBuffer imageBuffer;

    OutputConfig outputConfig;

    std::unique_ptr<Scene> scene;
};

#endif // RAYTRACER_RAYTRACER_H