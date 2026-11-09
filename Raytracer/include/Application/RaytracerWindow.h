#ifndef APPLICATION_RAYTRACER_WINDOW_H
#define APPLICATION_RAYTRACER_WINDOW_H

#include <QMainWindow>

class RaytracerController;
class QComboBox;
class QProgressBar;
class RenderPanel;

class RaytracerWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit RaytracerWindow(QWidget* parent = nullptr, std::string name = "Raytracer", int w = 800, int h = 600);
	~RaytracerWindow() override = default;

	RaytracerController* GetRaytracerController() { return raytracerController; }
	const RaytracerController* GetRaytracerController() const { return raytracerController; }

private:
	void SetupUI(std::string name, int w, int h);
	void SetupConnections();
	void ApplyStyle();

	QComboBox* sceneSelector;
	QProgressBar* progressBar;
	RenderPanel* renderPanel;

	RaytracerController* raytracerController;
};

#endif // APPLICATION_RAYTRACER_WINDOW_H