#ifndef RAYTRACER_APPLICATION_RENDER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PANEL_H

#include <QWidget>

class QPushButton;
class QProgressBar;

class RenderPanel : public QWidget
{
	Q_OBJECT

public:
	explicit RenderPanel(QWidget* parent = nullptr);

	void UpdateProgressBar(int percentage);
	void OnRenderEnded();

signals:
	void RenderRequested();
	void CancelRequested();

private:
	void SetupUI();
	void SetupConnections();

	QProgressBar* progressBar;
	QPushButton* renderButton;
	QPushButton* cancelButton;
};

#endif // RAYTRACER_APPLICATION_RENDER_PANEL_H