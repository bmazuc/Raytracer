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
	/**
	 *  Handles window closing and rendering thread cleanup.
	 *
	 * Ensures that an ongoing rendering operation is properly stopped
	 * before the main application window is destroyed.
	 * 
	 * @param event Window close event
	 */
	void closeEvent(QCloseEvent* event) override;

	/**
	 * Initializes the different panels and configures
	 * the main window layout.
	 */
	void SetupUI();
	/**
	 * Connects user interactions, rendering notifications
	 * and image updates to their corresponding handlers.
	 */
	void SetupConnections();
	/**
	 * Configures the appearance of the main window and its widgets.
	 */
	void ApplyStyle();

	// Panel displaying the current operation state and progress
	OperationStatusPanel* operationStatusPanel;
	// Panel containing render and cancellation controls
	RenderPanel* renderPanel;
	// Panel configuring the output directory and filename
	OutputPanel* outputPanel;
	// Panel displaying the rendered image
	ImageViewPanel* imageViewPanel;
	// Panel configuring renderer parameters
	RenderParameterPanel* renderParameterPanel;
	// Panel selecting the JSON scene to load
	SceneFilePanel* sceneFilePanel;

	// Coordinates the GUI with the background rendering worker
	RenderController* renderController;
};

#endif // RAYTRACER_APPLICATION_RAYTRACER_WINDOW_H