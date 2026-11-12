#ifndef RAYTRACER_APPLICATION_WIDGET_HELPER_H
#define RAYTRACER_APPLICATION_WIDGET_HELPER_H

class QWidget;
class QPushButton;
class QLineEdit;

namespace WidgetHelper
{
	QPushButton* CreateBrowseButton(QLineEdit* associatedLineEdit, QWidget* parent = nullptr);
}

#endif // RAYTRACER_APPLICATION_WIDGET_HELPER_H