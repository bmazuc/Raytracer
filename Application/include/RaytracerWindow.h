#ifndef RAYTRACER_APPLICATION_RAYTRACER_WINDOW_H
#define RAYTRACER_APPLICATION_RAYTRACER_WINDOW_H

#include <QMainWindow>

class RenderController;
class RenderPanel;
class OutputPanel;
class ImageViewPanel;
class RenderParameterPanel;
class SceneFilePanel;
class OperationStatusPanel;

/**
 * Represents the main application window.
 * 
 * Coordinates the graphical interface by assembling the different
 * panels and connecting them to the rendering controller.
 *
 * Manages the application layout, visual styling and window events.
 */
class RaytracerWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit RaytracerWindow(std::string name = "Raytracer", int w = 1920, int h = 1080, QWidget* parent = nullptr);
	~RaytracerWindow() override = default;

	RenderController* GetRaytracerController() { return renderController; }
	const RenderController* GetRaytracerController() const { return renderController; }

private:
	void closeEvent(QCloseEvent* event) override;
	void SetupUI();
	void SetupConnections();
	void ApplyStyle();

	OperationStatusPanel* operationStatusPanel;
	RenderPanel* renderPanel;
	OutputPanel* outputPanel;
	ImageViewPanel* imageViewPanel;
	RenderParameterPanel* renderParameterPanel;
	SceneFilePanel* sceneFilePanel;

	RenderController* renderController;
};

#endif // RAYTRACER_APPLICATION_RAYTRACER_WINDOW_H