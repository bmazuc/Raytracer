#ifndef RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H

#include "Panel/GroupBoxPanel.h"

class QSlider;
class QLineEdit;
struct RendererConfiguration;

/**
 * Provides controls for configuring rendering parameters.
 */
class RenderParameterPanel : public GroupBoxPanel
{
	Q_OBJECT

public:
	using GroupBoxPanel::GroupBoxPanel;

	/**
	 * Retrieves the selected rendering parameters and converts
	 * them into a RendererConfiguration instance.
	 *
	 * @return Configuration generated from the current panel values.
	 */
	RendererConfiguration GenerateRendererConfig();

private:	
	QString GetGroupTitle() const override;
	void SetupUI() override;
	void SetupConnections() override;

	// Selects the worker-thread count used internally by the Renderer
	QSlider* threadCountSlider;
	// Displays the currently selected thread count
	QLabel* threadCountSliderValueLabel;
	// Input for the progress polling interval, in milliseconds
	QLineEdit* progressMonitorFrequencyEdit;
	// Input for the square rendering tile size, in pixels
	QLineEdit* tileSizeEdit;
};

#endif