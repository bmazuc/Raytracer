#ifndef RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H
#define RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H

#include <QObject>
#include <QPointer>

class QString;
class QThread;
class RenderWorker;
struct RendererConfig;
struct OutputConfig;
class QImage;

enum class OperationStatus;

/**
 * Coordinates rendering operations between the graphical
 * interface and the rendering worker.
 *
 * Manages the worker thread lifecycle, forwards rendering
 * configuration and handles progress, completion, cancellation
 * and error notifications through Qt signals.
 */
class RenderController : public QObject
{
	Q_OBJECT
public:
	explicit RenderController(QObject* parent = nullptr);
	~RenderController();

	void StartRender(const QString& scenePath, const RendererConfig& rendererConfig, const OutputConfig& outputConfig);
	void StopRender();

signals: 
	void ProgressChanged(int percentage);
	void OperationStatusChanged(OperationStatus status);
	void ImageReady(const QImage& image);
	void RenderFinished();
	void RenderCancelled();
	void RenderError(const QString& error);

private:
	RenderWorker* worker = nullptr;
	QPointer<QThread> renderThread;
	bool isRendering = false;
};

#endif // RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H