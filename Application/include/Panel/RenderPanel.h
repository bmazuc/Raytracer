#ifndef RAYTRACER_APPLICATION_RENDER_PANEL_H
#define RAYTRACER_APPLICATION_RENDER_PANEL_H

#include "Panel/Panel.h"

class QPushButton;

/**
 * Provides the interface controls for starting and cancelling
 * rendering operations.
 */
class RenderPanel : public Panel
{
	Q_OBJECT

public:
	using Panel::Panel;

	void OnRenderStart();
	void OnRenderEnded();

signals:
	void RenderRequested();
	void CancelRequested();

private:
	void SetupUI() override;
	void SetupConnections() override;
	
	QPushButton* renderButton;
	QPushButton* cancelButton;
};

#endif // RAYTRACER_APPLICATION_RENDER_PANEL_H