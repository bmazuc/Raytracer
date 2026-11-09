#ifndef APPLICATION_RAYTRACER_WINDOW_H
#define APPLICATION_RAYTRACER_WINDOW_H

#include <QMainWindow>

class RenderController;
class QComboBox;
class QProgressBar;
class RenderPanel;

class RaytracerWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit RaytracerWindow(QWidget* parent = nullptr, std::string name = "Raytracer", int w = 800, int h = 600);
	~RaytracerWindow() override = default;

	RenderController* GetRaytracerController() { return renderController; }
	const RenderController* GetRaytracerController() const { return renderController; }

private:
	void closeEvent(QCloseEvent* event) override;
	void SetupUI(std::string name, int w, int h);
	void SetupConnections();
	void ApplyStyle();

	QComboBox* sceneSelector;
	QProgressBar* progressBar;
	RenderPanel* renderPanel;

	RenderController* renderController;
};

#endif // APPLICATION_RAYTRACER_WINDOW_H