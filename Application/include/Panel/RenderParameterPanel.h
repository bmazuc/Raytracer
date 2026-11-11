#ifndef RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H

#include <QWidget>

class QSlider;
class QLineEdit;
struct RendererConfig;

class RenderParameterPanel : public QWidget
{
	Q_OBJECT

public:
	explicit RenderParameterPanel(QWidget* parent = nullptr);

	RendererConfig GenerateRendererConfig();

private:
	void SetupUI();
	void SetupConnections();

	QSlider* threadCountSlider;
	QLabel* threadCountSliderValueLabel;
	QLineEdit* progressMonitorFrequencyEdit;
	QLineEdit* tileSizeEdit;
};

#endif