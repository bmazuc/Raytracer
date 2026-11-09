#include "Application/Worker/RenderWorker.h"

#include "Raytracer.h"
#include "Scene/Scene.h"

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

void RenderWorker::SetCameraConfig(const CameraConfiguration& config)
{
	raytracer->GetCamera()->SetCameraConfig(config);
}

void RenderWorker::SetScene(std::unique_ptr<Scene> scene)
{
	raytracer->SetScene(std::move(scene));
}

void RenderWorker::SetOutputConfig(const OutputConfig& outputConfig)
{
	raytracer->SetOutputConfig(outputConfig);
}