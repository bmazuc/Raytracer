#ifndef RAYTRACER_APPLICATION_WIDGET_HELPER_H
#define RAYTRACER_APPLICATION_WIDGET_HELPER_H

class QWidget;
class QPushButton;
class QLineEdit;

namespace WidgetHelper
{
	/**
	 * Create a button associated with a line edit for browsing
	 * files or folder and fill the line edit with it.
	 * 
	 * @param associatedLineEdit Input field receiving the selected directory.
	 * @param parent Parent widget.
	 * @return Pointer to the created browse button.
	 */
	QPushButton* CreateBrowseButton(QLineEdit* associatedLineEdit, QWidget* parent = nullptr);
}

#endif // RAYTRACER_APPLICATION_WIDGET_HELPER_H