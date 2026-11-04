#include "Raytracer.h"
#include "Scene/Scene.h"
#include "Image/ImageBuffer.h"
#include "Image/ImageWriterFactory.h"
#include "Image/ImageWriter.h"

Raytracer::Raytracer(const CameraConfiguration& cameraConfig, const RendererConfig& rendererConfig)
	: camera(cameraConfig), renderer(rendererConfig)
{
}

void Raytracer::SetScene(std::unique_ptr<Scene> newScene)
{
    scene = std::move(newScene);
}

void Raytracer::RenderToFile(std::string fileName)
{
    if (!scene)
    {
        return;
    }

    ImageBuffer imageBuffer = renderer.Render(camera, *scene, fileName);

    std::clog << "\rWriting image.                 " << std::flush;

    if (fileName.size() >= 4)
    {
        std::string extension = fileName.substr(fileName.size() - 4);
        std::unique_ptr<ImageWriter> writer = ImageWriterFactory::CreateImageWriter(extension);

        if (writer)
        {
            writer->Write(fileName, imageBuffer);
        }
    }

    std::clog << "\rDone.                 \n";
}