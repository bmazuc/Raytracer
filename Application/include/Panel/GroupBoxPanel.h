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
	/**
	 * Configure the section title.
	 */
	virtual QString GetGroupTitle() const = 0;
	/**
	 * Specifie which QBoxLayout class are used by group layout.
	 * Default are QVBoxLayout.
	 */
	virtual QBoxLayout* CreateGroupLayout();

	// Group box providing the panel's titled container.
	QGroupBox* groupBox;
	// Layout containing the widgets inside the group box.
	QBoxLayout* groupLayout;

private:
	/**
	 * Creates the group box, configures its title and layout,
	 * and integrates it into the panel's main layout
	 */
	void SetupContainer() override;
};

#endif // RAYTRACER_APPLICATION_GROUP_BOX_PANEL_H