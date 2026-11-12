#ifndef RAYTRACER_APPLICATION_LAYOUT_HELPER_H
#define RAYTRACER_APPLICATION_LAYOUT_HELPER_H

class QLayout;
class QFormLayout;

namespace LayoutHelper
{
	void SetupPanelLayout(QLayout* layout);
	void SetupFormLayout(QFormLayout* layout);
}

#endif // RAYTRACER_APPLICATION_LAYOUT_HELPER_H