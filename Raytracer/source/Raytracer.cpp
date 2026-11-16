#include "Raytracer.h"
#include "Scene/Scene.h"
#include "Image/ImageWriterFactory.h"
#include "Image/ImageWriter.h"

Raytracer::Raytracer()
    : camera(CameraConfiguration()), renderer(RendererConfiguration()), outputConfig(OutputConfiguration())
{
}

Raytracer::Raytracer(const CameraConfiguration& cameraConfig, const RendererConfiguration& rendererConfig)
	: camera(cameraConfig), renderer(rendererConfig)
{
}

const Scene* Raytracer::GetScene() const 
{ 
    return scene.get(); 
}

void Raytracer::SetScene(std::unique_ptr<Scene> newScene)
{
    scene = std::move(newScene);
}

void Raytracer::RenderToFile(const OperationStatusCallback& operationStatusCallback, const ProgressCallback& progressCallback, const std::atomic_bool& cancelRequested)
{
    if (!scene)
    {
        throw std::logic_error("Cannot render: no scene has been configured");
    }

    const std::size_t dotPosition = outputConfig.filename.find_last_of('.');
    if (dotPosition == std::string::npos)
    {
        throw std::invalid_argument("Output filename must have a supported extension");
    }

    const std::string extension = outputConfig.filename.substr(dotPosition);
    std::unique_ptr<ImageWriter> writer = ImageWriterFactory::CreateImageWriter(extension);
    if (!writer)
    {
        throw std::invalid_argument("Unsupported image format: " + extension);
    }

    if (operationStatusCallback)
    {
        operationStatusCallback(OperationStatus::RenderingScene);
    }

    imageBuffer = renderer.Render(camera, *scene, outputConfig.GetPath(), progressCallback, cancelRequested);

    if (!cancelRequested)
    {
        if (operationStatusCallback)
        {
            operationStatusCallback(OperationStatus::WritingToFile);
        }

        if (writer->Write(outputConfig.GetPath(), imageBuffer))
        {
            throw std::runtime_error("Failed to write image: " + outputConfig.GetPath());
        }
    }
}