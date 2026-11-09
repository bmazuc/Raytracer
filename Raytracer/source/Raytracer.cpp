#include "Raytracer.h"
#include "Scene/Scene.h"
#include "Image/ImageBuffer.h"
#include "Image/ImageWriterFactory.h"
#include "Image/ImageWriter.h"

Raytracer::Raytracer()
    : camera(CameraConfiguration()), renderer(RendererConfig()), outputConfig(OutputConfig())
{
}

Raytracer::Raytracer(const CameraConfiguration& cameraConfig, const RendererConfig& rendererConfig)
	: camera(cameraConfig), renderer(rendererConfig)
{
}

void Raytracer::SetScene(std::unique_ptr<Scene> newScene)
{
    scene = std::move(newScene);
}

void Raytracer::RenderToFile(const ProgressCallback& callback, const std::atomic_bool& cancelRequested)
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

    ImageBuffer imageBuffer = renderer.Render(camera, *scene, outputConfig.GetPath(), callback, cancelRequested);

    if (!cancelRequested)
    {

        std::clog << "\rWriting image.                 " << std::flush;

        if (writer->Write(outputConfig.GetPath(), imageBuffer))
        {
            throw std::runtime_error("Failed to write image: " + outputConfig.GetPath());
        }

        std::clog << "\rDone.                 \n";
    }
    else
    {
        std::clog << "\rCancelled.                 \n";
    }
}