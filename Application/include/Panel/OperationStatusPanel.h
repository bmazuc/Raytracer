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

	/**
	 * Sets the progress bar to reflect the percentage
	 * of completed rendering work.
	 *
	 * @param percentage Current progress percentage.
	 */
	void UpdateProgressBar(int percentage);
	/**
	 * Converts the current operation state into a user-friendly
	 * description displayed in the panel.
	 *
	 * @param status Current application operation status.
	 */
	void HandleOperationStatus(OperationStatus status);

protected:
	/**
	 * Performs any initialization required when the panel
	 * becomes visible.
	 *
	 * @param event Widget show event.
	 */
	void showEvent(QShowEvent* event) override;

private:
	QString GetGroupTitle() const override;
	void SetupUI() override;

	// Label displaying the current rendering operation state
	QLabel* operationStatusLabel;
	// Progress indicator updated as rendering tiles are completed
	QProgressBar* progressBar;
};

#endif // RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H