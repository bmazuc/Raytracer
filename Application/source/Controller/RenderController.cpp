#include "Controller/RenderController.h"
#include "Raytracer.h"
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

void RenderController::StartRender(const QString& scenePath, const RendererConfig& rendererConfig, const OutputConfig& outputConfig)
{
    if (isRendering)
    {
        return;
    }

    isRendering = true;

    QThread* thread = new QThread(this);
    worker = new RenderWorker();
    worker->SetOutputConfig(outputConfig);
    worker->SetRendererConfig(rendererConfig);

    renderThread = thread;

    worker->moveToThread(thread);

    worker->LoadScene(scenePath.toStdString());

    connect(thread, &QThread::started, worker, &RenderWorker::Run);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this,
        [this]()
        {
            isRendering = false;
            renderThread = nullptr;
        }
    );

    connect(worker, &RenderWorker::ImageReady, this, &RenderController::ImageReady);
    connect(worker, &RenderWorker::ProgressChanged,this,&RenderController::ProgressChanged);
    connect(worker, &RenderWorker::OperationStatusChanged, this, &RenderController::OperationStatusChanged);

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