#ifndef RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H
#define RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H

#include <QObject>
#include <QPointer>

class Raytracer;
class QThread;
class RenderWorker;
struct RendererConfig;
struct OutputConfig;
class QImage;

enum class OperationStatus;

class RenderController : public QObject
{
	Q_OBJECT
public:
	explicit RenderController(QObject* parent = nullptr);
	~RenderController();

	void StartRender(int sceneIdx, const RendererConfig& rendererConfig, const OutputConfig& outputConfig);
	void StopRender();

signals: 
	void ProgressChanged(int percentage);
	void OperationStatusChanged(OperationStatus status);
	void ImageReady(const QImage& image);
	void RenderFinished();
	void RenderCancelled();
	void RenderError(const QString& error);

private:
	void SetWorkerAsBasicScene();
	void SetWorkerAsComplexScene();

	RenderWorker* worker = nullptr;
	QPointer<QThread> renderThread;
	bool isRendering = false;
};

#endif // RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H