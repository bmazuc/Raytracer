#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "Renderer.h"
#include "Camera.h"
#include "Image/ImageBuffer.h"

#include <memory>

class Scene;
struct CameraConfiguration;
struct RendererConfiguration;

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
struct OutputConfiguration
{
public:
    // Destination directory for the rendered image
    std::string directory;
    // Output filename, including its extension
    std::string filename;

    /**
     * Combines the destination directory and filename into
     * a single filesystem path.
     *
     * @return Complete output file path.
     */
    std::string GetPath() { return directory + '/' + filename; }
};

/**
 * Progress callback allows to retrieve completion percentage
 * and use it elsewhere.
 */
using ProgressCallback = std::function<void(int)>;
/**
 * Progress callback allows to retrieve current operation status
 * and use it elsewhere.
 */
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
    Raytracer(const CameraConfiguration& cameraConfig, const RendererConfiguration& rendererConfig);

    Camera* GetCamera() { return &camera; }
    const Camera* GetCamera() const { return &camera; }

    Scene* GetScene() { return scene.get(); }
    const Scene* GetScene() const;

    Renderer* GetRenderer() { return &renderer; }
    const Renderer* GetRenderer() const { return &renderer; }

    ImageBuffer& GetImageBuffer() { return imageBuffer; }
    const ImageBuffer& GetImageBuffer() const { return imageBuffer; }

    void SetOutputConfig(const OutputConfiguration& inOutputConfig) { outputConfig = inOutputConfig; }
    /**
     * Replaces the current scene.
     * Transfers ownership of the provided scene to the ray tracing engine.
     *
     * @param newScene Scene to be managed by the ray tracer.
     */
    void SetScene(std::unique_ptr<Scene> newScene);

    /**
     * Executes the complete rendering and image export workflow.
     *
     * Reports operation status changes and rendering progress through
     * the provided callbacks.
     *
     * Supports cancellation and handles the transition between
     * scene loading, rendering and image writing.
     *
     * @param operationStatusCallback Callback used to report operation stages.
     * @param progressCallback Callback used to report rendering progress.
     * @param cancelRequested Atomic cancellation flag.
     */
    void RenderToFile(const OperationStatusCallback& operationStatusCallback, const ProgressCallback& progressCallback, const std::atomic_bool& cancelRequested);

private:
    // Rendering engine responsible for tracing image tiles
    Renderer renderer;
    // Camera used to generate primary rays
    Camera camera;

    // Pixel buffer produced by the current render operation
    ImageBuffer imageBuffer;

    // Destination settings used by the image export stage
    OutputConfiguration outputConfig;

    // Scene owned by this ray tracing instance
    std::unique_ptr<Scene> scene;
};

#endif // RAYTRACER_RAYTRACER_H