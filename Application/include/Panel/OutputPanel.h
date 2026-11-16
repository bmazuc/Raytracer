#ifndef RAYTRACER_APPLICATION_OUTPUT_PANEL_H
#define RAYTRACER_APPLICATION_OUTPUT_PANEL_H

#include "Panel/GroupBoxPanel.h"

class QLineEdit;
class QPushButton;
struct OutputConfig;

/**
 * Provides controls for configuring the rendered image destination.
 */
class OutputPanel : public GroupBoxPanel
{
	Q_OBJECT

public:
	using GroupBoxPanel::GroupBoxPanel;

	/**
	 * Generates the OutputConfig from the selected
	 * output directory and filename.
	 */
	OutputConfig GenerateOutputConfig();

private:
	QString GetGroupTitle() const override;

	void SetupUI() override;
	void SetupConnections() override;

	void BrowseDirectory();

	QLineEdit* directoryEdit;
	QLineEdit* fileEdit;
	QPushButton* browseButton;
};

#endif // RAYTRACER_APPLICATION_OUTPUT_PANEL_H