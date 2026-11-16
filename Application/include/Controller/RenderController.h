#ifndef RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H
#define RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H

#include <QObject>
#include <QPointer>

class QString;
class QThread;
class RenderWorker;
struct RendererConfiguration;
struct OutputConfiguration;
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
	
	/**
	 * Stop rendering and clean thread.
	 */
	~RenderController();

	/**
	 * Starts a rendering operation on a dedicated worker thread.
	 * 
	 * Creates and configures the rendering worker, initializes
     * its execution thread and forwards rendering notifications
     * to the graphical interface.
	 *
	 * @param scenePath Path to the JSON scene file.
     * @param rendererConfig Configuration of the rendering process.
	 * @param outputConfig Destination configuration for the rendered image.
	 */
	void StartRender(const QString& scenePath, const RendererConfiguration& rendererConfig, const OutputConfiguration& outputConfig);
	/**
	 * Requests cancellation of the current rendering operation.
	 *
	 * Signals the worker to stop rendering and handles
	 * the associated thread lifecycle.
	 */
	void StopRender();

signals: 
	void ProgressChanged(int percentage);
	void OperationStatusChanged(OperationStatus status);
	void ImageReady(const QImage& image);
	void RenderFinished();
	void RenderCancelled();
	void RenderError(const QString& error);

private:
	// Worker object moved to the dedicated rendering QThread
	RenderWorker* worker = nullptr;
	// Guarded pointer to the Qt thread executing the worker
	QPointer<QThread> renderThread;
	// Tracks whether a rendering operation is currently active
	bool isRendering = false;
};

#endif // RAYTRACER_APPLICATION_RAYTRACER_CONTROLLER_H