#ifndef RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H
#define RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H

#include <QWidget>

enum class OperationStatus;
class QLabel;
class QProgressBar;

class OperationStatusPanel : public QWidget
{
	Q_OBJECT

public:
	explicit OperationStatusPanel(QWidget* parent = nullptr);

	void UpdateProgressBar(int percentage);
	void HandleOperationStatus(OperationStatus status);

protected:
	void showEvent(QShowEvent* event) override;

private:
	void SetupUI();

	QLabel* operationStatusLabel;
	QProgressBar* progressBar;
};

#endif // RAYTRACER_APPLICATION_OPERATION_STATUS_PANEL_H