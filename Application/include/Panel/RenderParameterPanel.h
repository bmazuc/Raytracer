#ifndef RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PARAMETER_PANEL_H

#include <QWidget>

class QComboBox;
class QSlider;
class QLineEdit;
struct RendererConfig;

class RenderParameterPanel : public QWidget
{
	Q_OBJECT

public:
	explicit RenderParameterPanel(QWidget* parent = nullptr);

	void AddScene(const QString& text, int index);
	int GetSceneIndex();
	RendererConfig GenerateRendererConfig();

private:
	void SetupUI();
	void SetupConnections();

	QSlider* threadCountSlider;
	QLabel* threadCountSliderValueLabel;
	QLineEdit* progressMonitorFrequencyEdit;
	QLineEdit* tileSizeEdit;

	QComboBox* sceneSelector;
};

#endif