#ifndef RAYTRACER_APPLICATION_LAYOUT_HELPER_H
#define RAYTRACER_APPLICATION_LAYOUT_HELPER_H

class QLayout;
class QFormLayout;

/**
 * Provides reusable functions for configuring Qt layouts.
 */
namespace LayoutHelper
{
	/**
	 * Configures shared margins and spacing values to maintain
	 * consistent layout presentation across the application.
	 *
	 * @param layout Layout to configure.
	 */
	void SetupPanelLayout(QLayout* layout);

	/**
	 * Sets the horizontal and vertical spacing used by form controls.
	 *
	 * @param layout Form layout to configure.
	 */
	void SetupFormLayout(QFormLayout* layout);
}

#endif // RAYTRACER_APPLICATION_LAYOUT_HELPER_H