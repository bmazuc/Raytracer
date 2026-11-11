#include "Worker/RenderWorker.h"
#include "Utils/ImageConverter.h"
#include "Raytracer.h"
#include "Scene/Scene.h"
#include "Serialization/SceneSerializer.h"

RenderWorker::RenderWorker(QObject* parent)
	: QObject(parent),
	raytracer(std::make_unique<Raytracer>())
{
}

void RenderWorker::RequestCancel()
{
	cancelRequested.store(true);
}

void RenderWorker::Run()
{
	try
	{
		raytracer->RenderToFile(
			[this](OperationStatus status)
			{
				emit OperationStatusChanged(status);
			},
			[this](int percentage)
			{
				emit ProgressChanged(percentage);
			},
			cancelRequested
		);

		if (cancelRequested.load())
		{
			emit RenderCancelled();
		}
		else
		{
			const ImageBuffer& buffer = raytracer->GetImageBuffer();

			QImage image = ImageConverter::ToQImage(buffer);
			if (image.isNull())
			{
				throw std::runtime_error("Failed to convert rendered image");
			}

			emit ImageReady(image);


			emit RenderFinished();
		}
	}
	catch (const std::exception& e)
	{
		emit RenderError(QString::fromUtf8(e.what()));
	}
	catch (...)
	{
		emit RenderError("Unknown rendering error");
	}
}

void RenderWorker::LoadScene(std::string jsonpath)
{
	SceneSerializer::Load(jsonpath, raytracer);
}

void RenderWorker::SetRendererConfig(const RendererConfig& config)
{
	raytracer->GetRenderer()->SetRendererConfig(config);
}

void RenderWorker::SetConfiguration(const CameraConfiguration& config)
{
	raytracer->GetCamera()->SetConfiguration(config);
}

void RenderWorker::SetScene(std::unique_ptr<Scene> scene)
{
	raytracer->SetScene(std::move(scene));
}

void RenderWorker::SetOutputConfig(const OutputConfig& outputConfig)
{
	raytracer->SetOutputConfig(outputConfig);
}