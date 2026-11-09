#include "Application/Panel/OutputPanel.h"
#include "Raytracer.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QCoreApplication>

OutputPanel::OutputPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void OutputPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QHBoxLayout* directoryLayout = new QHBoxLayout();

	QLabel* directoryLabel = new QLabel("Output directory", this);

	QString defaultDirectory = QCoreApplication::applicationDirPath();
	directoryEdit = new QLineEdit(defaultDirectory, this);

	browseButton = new QPushButton(this);
	browseButton->setIcon(QIcon(":/icons/folder.png"));
	browseButton->setFixedSize(32, 32);

	QLabel* fileLabel = new QLabel("File name", this);
	fileEdit = new QLineEdit("image.png", this);

	directoryLayout->addWidget(directoryEdit);
	directoryLayout->addWidget(browseButton);

	mainLayout->addWidget(directoryLabel);
	mainLayout->addLayout(directoryLayout);
	mainLayout->addWidget(fileLabel);
	mainLayout->addWidget(fileEdit);

	setLayout(mainLayout);
}

void OutputPanel::SetupConnections()
{
	connect(browseButton,
		&QPushButton::clicked,
		this,
		&OutputPanel::BrowseDirectory);
}

void OutputPanel::BrowseDirectory()
{
	QString directory = QFileDialog::getExistingDirectory(
		this,
		"Select output directory",
		directoryEdit->text(),
		QFileDialog::ShowDirsOnly
	);

	if (!directory.isEmpty())
	{
		directoryEdit->setText(directory);
	}
}

OutputConfig OutputPanel::GenerateOutputConfig()
{
	OutputConfig config;
	config.directory = directoryEdit->text().toStdString();
	config.filename = fileEdit->text().toStdString();
	return config;
}