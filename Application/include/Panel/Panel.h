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

	void InitPanel();

protected:
	virtual void SetupUI() = 0;
	virtual void SetupConnections() {};
	virtual void SetupContainer() {};

	virtual QBoxLayout* CreateMainLayout();

	QBoxLayout* mainLayout;
};

#endif // RAYTRACER_APPLICATION_PANEL_H