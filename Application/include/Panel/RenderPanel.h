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

	/**
	 * Disables the render button and enables the cancellation button
	 * to reflect the current rendering state.
	 */
	void OnRenderStart();
	/**
	 * Re-enables the render button and disables the cancellation button.
	 */
	void OnRenderEnded();

signals:
	void RenderRequested();
	void CancelRequested();

private:
	void SetupUI() override;
	void SetupConnections() override;
	
	// Starts a new rendering operation
	QPushButton* renderButton;
	// Requests cancellation of the active rendering operation
	QPushButton* cancelButton;
};

#endif // RAYTRACER_APPLICATION_RENDER_PANEL_H