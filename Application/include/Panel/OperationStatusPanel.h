#ifndef RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H
#define RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H

#include "Panel/GroupBoxPanel.h"

enum class OperationStatus;
class QLabel;
class QProgressBar;

/**
 * Displays the current rendering operation status and progress.
 *
 * Updates the progress bar and operation status label
 * according to notifications received from the rendering workflow.
 */
class OperationStatusPanel : public GroupBoxPanel
{
	Q_OBJECT

public:
	using GroupBoxPanel::GroupBoxPanel;

	void UpdateProgressBar(int percentage);
	void HandleOperationStatus(OperationStatus status);

protected:
	void showEvent(QShowEvent* event) override;

private:
	QString GetGroupTitle() const override;
	void SetupUI() override;

	QLabel* operationStatusLabel;
	QProgressBar* progressBar;
};

#endif // RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H