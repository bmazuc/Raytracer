#ifndef RAYTRACER_RAYTRACER_CONTROLLER_H
#define RAYTRACER_RAYTRACER_CONTROLLER_H

#include <QObject>

class Raytracer;

class RaytracerController : public QObject
{
	Q_OBJECT
public:
	explicit RaytracerController(QObject* parent = nullptr);
	~RaytracerController() override = default;

	void SetOutputFile(const char* inOutputFile) { outputFile = inOutputFile; }

	void StartRender(int sceneIdx);
	void RenderBasicScene();
	void RenderComplexScene();
	void DeleteImage();

signals: 
	void ProgressChanged(int percentage);

private:
	std::unique_ptr<Raytracer> raytracer;
	const char* outputFile;
};

#endif // RAYTRACER_RAYTRACER_CONTROLLER_H