#include "Controller/RenderController.h"
#include "Raytracer.h"
#include "ExampleScenes/BasicScene.h"
#include "ExampleScenes/ComplexScene.h"
#include "Camera.h"
#include "Worker/RenderWorker.h"

#include <QThread>

#include <filesystem>

RenderController::RenderController(QObject* parent)
	: QObject(parent)
{
}

RenderController::~RenderController()
{
    if (renderThread && renderThread->isRunning())
    {
        StopRender();

        renderThread->quit();
        renderThread->wait();
    }
}

void RenderController::StartRender(int sceneIdx, const OutputConfig& outputConfig)
{
    if (isRendering)
    {
        return;
    }

    isRendering = true;

    QThread* thread = new QThread(this);
    worker = new RenderWorker();
    worker->SetOutputConfig(outputConfig);

    renderThread = thread;

    worker->moveToThread(thread);

    switch (sceneIdx)
    {
        case 0:
            SetWorkerAsBasicScene();
            break;
        case 1:
            SetWorkerAsComplexScene();
            break;
        default:break;
    }

    connect(thread, &QThread::started, worker, &RenderWorker::Run);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this,
        [this]()
        {
            isRendering = false;
            renderThread = nullptr;
        }
    );

    connect(worker, &RenderWorker::ProgressChanged,this,&RenderController::ProgressChanged);

    connect(worker, &RenderWorker::RenderError, this, &RenderController::RenderError);
    connect(worker, &RenderWorker::RenderError, worker, &QObject::deleteLater);
    connect(worker, &RenderWorker::RenderError, thread, &QThread::quit);
    connect(worker, &RenderWorker::RenderError, this,
        [this](const QString& error)
        {
            isRendering = false;
            emit RenderError(error);
        }
    );

    connect(worker, &RenderWorker::RenderFinished, this, &RenderController::RenderFinished);
    connect(worker, &RenderWorker::RenderFinished, thread, &QThread::quit);
    connect(worker, &RenderWorker::RenderFinished, worker, &QObject::deleteLater);
    connect(worker, &RenderWorker::RenderFinished, this,
        [this]()
        {
            isRendering = false;
            emit RenderFinished();
        }
    );

    connect(worker, &RenderWorker::RenderCancelled, this, &RenderController::RenderCancelled);
    connect(worker, &RenderWorker::RenderCancelled, thread, &QThread::quit);
    connect(worker, &RenderWorker::RenderCancelled, worker, &QObject::deleteLater);
    connect(worker, &RenderWorker::RenderCancelled, this,
        [this]()
        {
            isRendering = false;
            emit RenderCancelled();
        }
    );

    thread->start();
}

void RenderController::StopRender()
{
    if (worker)
    {
        worker->RequestCancel();
    }
}

void RenderController::SetWorkerAsBasicScene()
{
    if (!worker)
    {
        return;
    }

    CameraConfiguration cameraConfig;
    cameraConfig.imageWidth = 400;
    cameraConfig.aspectRatio = 16.0f / 9.0f;
    cameraConfig.samplesPerPixel = 100;
    cameraConfig.maxDepth = 50;

    cameraConfig.fov = 20;
    cameraConfig.position = Vec3(-2.0f, 2.0f, 1.0f);
    cameraConfig.lookAt = Vec3(0.0f, 0.0f, -1.0f);
    cameraConfig.vUp = Vec3(0.0f, 1.0f, 0.0f);

    cameraConfig.defocusAngle = 0.0f;
    cameraConfig.focusDistance = 10.0f;

    worker->SetCameraConfig(cameraConfig);
    worker->SetScene(BasicScene::Create());
}

void RenderController::SetWorkerAsComplexScene()
{
    if (!worker)
    {
        return;
    }

    CameraConfiguration cameraConfig;
    cameraConfig.imageWidth = 1200;
    cameraConfig.aspectRatio = 16.0f / 9.0f;
    cameraConfig.samplesPerPixel = 500;
    cameraConfig.maxDepth = 50;

    cameraConfig.fov = 20;
    cameraConfig.position = Vec3(13.0f, 2.0f, 3.0f);
    cameraConfig.lookAt = Vec3(0.0f, 0.0f, 0.0f);
    cameraConfig.vUp = Vec3(0.0f, 1.0f, 0.0f);

    cameraConfig.defocusAngle = 0.6f;
    cameraConfig.focusDistance = 10.0f;

    worker->SetCameraConfig(cameraConfig);
    worker->SetScene(ComplexScene::Create());
}