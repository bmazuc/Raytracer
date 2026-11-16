#ifndef RAYTRACER_APPLICATION_RENDER_WORKER_H
#define RAYTRACER_APPLICATION_RENDER_WORKER_H

#include <QObject>
#include <memory>

class QImage;
class Raytracer;
struct CameraConfiguration;
struct RendererConfig;
struct OutputConfig;
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

	void SetRendererConfig(const RendererConfig& config);
	void SetConfiguration(const CameraConfiguration& config);
	void SetScene(std::unique_ptr<Scene> scene);
	void SetOutputConfig(const OutputConfig& outputConfig);

	void LoadScene(std::string jsonpath);

	void RequestCancel();

public slots:
	void Run();

signals:
	void ProgressChanged(int percentage);
	void OperationStatusChanged(OperationStatus status);
	void ImageReady(const QImage& image);
	void RenderCancelled();
	void RenderFinished();
	void RenderError(const QString& error);

private:
	std::unique_ptr<Raytracer> raytracer;
	std::string outputFile;
	std::atomic_bool cancelRequested = false;
};

#endif // RAYTRACER_APPLICATION_RENDER_WORKER_H