#ifndef RAYTRACER_APPLICATION_PANEL_H
#define RAYTRACER_APPLICATION_PANEL_H

#include <QWidget>

class QBoxLayout;

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