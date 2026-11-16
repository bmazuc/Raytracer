#ifndef RAYTRACER_APPLICATION_RENDER_WORKER_H
#define RAYTRACER_APPLICATION_RENDER_WORKER_H

#include <QObject>
#include <memory>

class QImage;
class Raytracer;
struct CameraConfiguration;
struct RendererConfiguration;
struct OutputConfiguration;
class Scene;
enum class OperationStatus;

/**
 * Executes rendering operations independently of the GUI thread.
 *
 * Manages the ray tracing engine, scene loading, rendering
 * configuration and output settings.
 * 
 * Reports operation progress and results through Qt signals
 * and supports rendering cancellation.
 */
class RenderWorker : public QObject
{
	Q_OBJECT

public:
	explicit RenderWorker(QObject* parent = nullptr);

	/**
	 * Updates the renderer configuration used by the worker.
	 *
	 * @param config New rendering configuration.
	 */
	void SetRendererConfiguration(const RendererConfiguration& config);
	/**
	 * Updates the camera configuration used by the worker.
	 *
	 * @param config New camera configuration.
	 */
	void SetCameraConfiguration(const CameraConfiguration& config);
	/**
	 * Assigns the scene to be rendered.
	 * Transfers ownership of the scene to the worker.
	 *
	 * @param scene Scene to render.
	 */
	void SetScene(std::unique_ptr<Scene> scene);
	/**
	 * Updates the destination configuration for the rendered image.
	 *
	 * @param outputConfig New image output configuration.
	 */
	void SetOutputConfig(const OutputConfiguration& outputConfig);

	/**
	 * Uses the scene serialization system to reconstruct
	 * the scene and its associated camera configuration.
	 *
	 * @param jsonpath Path to the JSON scene file.
	 */
	void LoadScene(std::string jsonpath);

	/**
	 * Requests cancellation of the current rendering operation.
	 */
	void RequestCancel();

public slots:
	/**
	 * Loads the scene, initializes the ray tracing engine,
	 * performs the rendering operation and reports progress,
	 * completion or errors through Qt signals.
	 *
	 * Handles cancellation requests and image export.
	 */
	void Run();

signals:
	void ProgressChanged(int percentage);
	void OperationStatusChanged(OperationStatus status);
	void ImageReady(const QImage& image);
	void RenderCancelled();
	void RenderFinished();
	void RenderError(const QString& error);

private:
	//  Ray tracing engine owned and executed by this worker
	std::unique_ptr<Raytracer> raytracer;
	// Output path associated with the current rendering operation
	std::string outputFile;
	// Thread-safe cancellation flag observed by the ray tracer
	std::atomic_bool cancelRequested = false;
};

#endif // RAYTRACER_APPLICATION_RENDER_WORKER_H