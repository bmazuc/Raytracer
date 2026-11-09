#ifndef RAYTRACER_RAYTRACER_CONTROLLER_H
#define RAYTRACER_RAYTRACER_CONTROLLER_H

#include <QObject>
#include <QPointer>

class Raytracer;
class QThread;
class RenderWorker;

class RenderController : public QObject
{
	Q_OBJECT
public:
	explicit RenderController(QObject* parent = nullptr);
	~RenderController();

	void SetOutputFile(const char* inOutputFile) { outputFile = inOutputFile; }

	void StartRender(int sceneIdx);
	void StopRender();

signals: 
	void ProgressChanged(int percentage);
	void RenderFinished();
	void RenderCancelled();
	void RenderError(const QString& error);

private:
	void SetWorkerAsBasicScene();
	void SetWorkerAsComplexScene();

	const char* outputFile;

	RenderWorker* worker = nullptr;
	QPointer<QThread> renderThread;
	bool isRendering = false;
};

#endif // RAYTRACER_RAYTRACER_CONTROLLER_H