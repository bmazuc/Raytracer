#ifndef RAYTRACER_APPLICATION_RENDER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PANEL_H

#include <QWidget>

class QPushButton;

class RenderPanel : public QWidget
{
	Q_OBJECT

public:
	explicit RenderPanel(QWidget* parent = nullptr);

	void OnRenderStart();
	void OnRenderEnded();

signals:
	void RenderRequested();
	void CancelRequested();

private:
	void SetupUI();
	void SetupConnections();
	
	QPushButton* renderButton;
	QPushButton* cancelButton;
};

#endif // RAYTRACER_APPLICATION_RENDER_PANEL_H