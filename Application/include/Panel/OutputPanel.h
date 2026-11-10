#ifndef RAYTRACER_APPLICATION_OUTPUT_PANEL_H
#define RAYTRACER_APPLICATION_OUTPUT_PANEL_H

#include <QWidget>

class QLineEdit;
class QPushButton;
struct OutputConfig;

class OutputPanel : public QWidget
{
	Q_OBJECT

public:
	explicit OutputPanel(QWidget* parent = nullptr);

	OutputConfig GenerateOutputConfig();

private:
	void SetupUI();
	void SetupConnections();

	void BrowseDirectory();

	QLineEdit* directoryEdit;
	QLineEdit* fileEdit;
	QPushButton* browseButton;
};

#endif // RAYTRACER_APPLICATION_OUTPUT_PANEL_H