#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "Renderer.h"
#include "Camera.h"
#include "Image/ImageBuffer.h"

#include <memory>

class Scene;
struct CameraConfiguration;
struct RendererConfig;

/**
 * Defines the different stages of a rendering operation.
 */
enum class OperationStatus
{
    LoadingScene,
    RenderingScene,
    WritingToFile
};

/**
 * Stores the destination directory and filename
 * used to save the rendered image
 */
struct OutputConfig
{
public:
    std::string directory;
    std::string filename;

    /**
     * Construct the complete output file path.
     */
    std::string GetPath() { return directory + '/' + filename; }
};

using ProgressCallback = std::function<void(int)>;
using OperationStatusCallback = std::function<void(OperationStatus)>;

/**
 * Core ray tracing engine class.
 * 
 * Owns and coordinates the renderer, camera, image buffer
 * and scene.
 * 
 * Handles the complete rendering workflow, from scene preparation
 * to saving the final image.
 */
class Raytracer
{
public:
    Raytracer();
    Raytracer(const CameraConfiguration& cameraConfig, const RendererConfig& rendererConfig);

    Camera* GetCamera() { return &camera; }
    const Camera* GetCamera() const { return &camera; }

    Scene* GetScene() { return scene.get(); }
    const Scene* GetScene() const;

    Renderer* GetRenderer() { return &renderer; }
    const Renderer* GetRenderer() const { return &renderer; }

    ImageBuffer& GetImageBuffer() { return imageBuffer; }
    const ImageBuffer& GetImageBuffer() const { return imageBuffer; }

    void SetOutputConfig(const OutputConfig& inOutputConfig) { outputConfig = inOutputConfig; }
    void SetScene(std::unique_ptr<Scene> newScene);

    void RenderToFile(const OperationStatusCallback& operationStatusCallback, const ProgressCallback& progressCallback, const std::atomic_bool& cancelRequested);

private:
    Renderer renderer;
    Camera camera;

    ImageBuffer imageBuffer;

    OutputConfig outputConfig;

    std::unique_ptr<Scene> scene;
};

#endif // RAYTRACER_RAYTRACER_H