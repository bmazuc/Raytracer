#ifndef RAYTRACER_APPLICATION_RENDER_WORKER_H
#define RAYTRACER_APPLICATION_RENDER_WORKER_H

#include <QObject>
#include <memory>

class QImage;
class Raytracer;
struct CameraConfiguration;
struct OutputConfig;
class Scene;

class RenderWorker : public QObject
{
	Q_OBJECT
public:
	explicit RenderWorker(QObject* parent = nullptr);

	void SetCameraConfig(const CameraConfiguration& config);
	void SetScene(std::unique_ptr<Scene> scene);
	void SetOutputConfig(const OutputConfig& outputConfig);

	void RequestCancel();

public slots:
	void Run();

signals:
	void ProgressChanged(int percentage);
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