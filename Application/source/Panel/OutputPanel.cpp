#include "Panel/OutputPanel.h"
#include "Raytracer.h"
#include "UI/LayoutHelper.h"
#include "UI/WidgetHelper.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QCoreApplication>
#include <QGroupBox>
#include <QStyle>

OutputPanel::OutputPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void OutputPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	LayoutHelper::SetupPanelLayout(mainLayout);

	QGroupBox* groupBox = new QGroupBox("Output", this);
	
	QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

	QFormLayout* formLayout = new QFormLayout();
	formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
	LayoutHelper::SetupFormLayout(formLayout);

	QString defaultDirectory = QCoreApplication::applicationDirPath();
	directoryEdit = new QLineEdit(defaultDirectory, groupBox);

	browseButton = WidgetHelper::CreateBrowseButton(directoryEdit, groupBox);

	QHBoxLayout* directoryLayout = new QHBoxLayout();
	directoryLayout->addWidget(directoryEdit, 1);
	directoryLayout->addWidget(browseButton);

	formLayout->addRow("Output directory", directoryLayout);

	fileEdit = new QLineEdit("image.png");

	formLayout->addRow("File name", fileEdit);

	groupLayout->addLayout(formLayout);

	mainLayout->addWidget(groupBox);
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