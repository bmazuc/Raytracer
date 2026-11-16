#ifndef RAYTRACER_APPLICATION_OUTPUT_PANEL_H
#define RAYTRACER_APPLICATION_OUTPUT_PANEL_H

#include "Panel/GroupBoxPanel.h"

class QLineEdit;
class QPushButton;
struct OutputConfiguration;

/**
 * Provides controls for configuring the rendered image destination.
 */
class OutputPanel : public GroupBoxPanel
{
	Q_OBJECT

public:
	using GroupBoxPanel::GroupBoxPanel;

	/**
	 * Retrieves the selected output directory and filename 
	 * and converts them into a OutputConfiguration instance.
	 *
	 * @return Output configuration generated from the panel values.
	 */
	OutputConfiguration GenerateOutputConfig();

private:
	QString GetGroupTitle() const override;

	void SetupUI() override;
	void SetupConnections() override;

	/**
	 * Opens a directory selection dialog
	 * and updates the corresponding input field.
	 */
	void BrowseDirectory();

	// Input field containing the output directory
	QLineEdit* directoryEdit;
	// Input field containing the output filename
	QLineEdit* fileEdit;
	// Opens the directory selection dialog
	QPushButton* browseButton;
};

#endif // RAYTRACER_APPLICATION_OUTPUT_PANEL_H