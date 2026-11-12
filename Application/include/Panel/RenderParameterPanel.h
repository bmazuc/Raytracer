#ifndef RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H

#include "Panel/GroupBoxPanel.h"

class QSlider;
class QLineEdit;
struct RendererConfig;

class RenderParameterPanel : public GroupBoxPanel
{
	Q_OBJECT

public:
	using GroupBoxPanel::GroupBoxPanel;

	RendererConfig GenerateRendererConfig();

private:	
	QString GetGroupTitle() const override;
	void SetupUI() override;
	void SetupConnections() override;

	QSlider* threadCountSlider;
	QLabel* threadCountSliderValueLabel;
	QLineEdit* progressMonitorFrequencyEdit;
	QLineEdit* tileSizeEdit;
};

#endif