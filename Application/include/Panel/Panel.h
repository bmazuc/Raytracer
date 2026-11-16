#ifndef RAYTRACER_APPLICATION_PANEL_H
#define RAYTRACER_APPLICATION_PANEL_H

#include <QWidget>

class QBoxLayout;

/**
 * Defines the common base class for application interface panels.
 *
 * Provides a shared initialization workflow and virtual methods
 * for configuring layouts, widgets and signal connections.
 */
class Panel : public QWidget
{
	Q_OBJECT

public:
	explicit Panel(QWidget* parent = nullptr);

	/**
	 * Creates the panel layout and invokes the corresponding
	 * setup methods for its container, widgets and connections.
	 */
	void InitPanel();

protected:
	/**
	 * Create and arrange panel's widgets.
	 */
	virtual void SetupUI() = 0;
	/**
	 * connect panel's widgets to the appropriate handlers.
 	 */
	virtual void SetupConnections() {};
	/**
	 * Configures the panel's main container.
	 *
	 * Can be overridden by derived panels to customize
	 * the layout container.
	 */
	virtual void SetupContainer() {};

	/**
	 * Specifie which QBoxLayout class are used by main layout.
	 * Default are QVBoxLayout.
	 */
	virtual QBoxLayout* CreateMainLayout();

	// Main layout used to arrange the panel's content.
	QBoxLayout* mainLayout;
};

#endif // RAYTRACER_APPLICATION_PANEL_H