#ifndef RAYTRACER_APPLICATION_GROUP_BOX_PANEL_H
#define RAYTRACER_APPLICATION_GROUP_BOX_PANEL_H

#include "Panel/Panel.h"

class QGroupBox;

class GroupBoxPanel : public Panel
{
	Q_OBJECT

public:
	using Panel::Panel;

protected:
	virtual QString GetGroupTitle() const = 0;
	virtual QBoxLayout* CreateGroupLayout();

	QGroupBox* groupBox;
	QBoxLayout* groupLayout;

private:
	void SetupContainer() override;
};

#endif // RAYTRACER_APPLICATION_GROUP_BOX_PANEL_H