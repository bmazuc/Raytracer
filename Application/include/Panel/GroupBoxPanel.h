#ifndef RAYTRACER_APPLICATION_GROUP_BOX_PANEL_H
#define RAYTRACER_APPLICATION_GROUP_BOX_PANEL_H

#include "Panel/Panel.h"

class QGroupBox;

/**
 * Extends the base panel with a group box container.
 *
 * Provides a common structure for panels that organize their
 * widgets inside a titled group box.
 */
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