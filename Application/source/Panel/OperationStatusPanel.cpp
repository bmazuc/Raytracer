#include "Panel/OperationStatusPanel.h"
#include "Raytracer.h"

#include <QProgressBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

OperationStatusPanel::OperationStatusPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
}

void OperationStatusPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(10, 10, 10, 10);
	mainLayout->setSpacing(8);

	QGroupBox* groupBox = new QGroupBox("Operation Status", this);
	QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

	// UpperLayout
	QHBoxLayout* upperLayout = new QHBoxLayout();
	
	operationStatusLabel = new QLabel("", groupBox);

	progressBar = new QProgressBar(groupBox);
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
	progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	progressBar->hide();

	upperLayout->addWidget(operationStatusLabel, 1);
	upperLayout->addWidget(progressBar, 2);

	groupLayout->addLayout(upperLayout);

	// LowerLayout
	QHBoxLayout* lowerLayout = new QHBoxLayout();

	QProgressBar* busyBar = new QProgressBar(groupBox);
	busyBar->setRange(0, 0);
	busyBar->setFixedWidth(100);

	lowerLayout->addStretch();
	lowerLayout->addWidget(busyBar);

	groupLayout->addLayout(lowerLayout);

	mainLayout->addWidget(groupBox);
}

void OperationStatusPanel::showEvent(QShowEvent* event)
{
	progressBar->setValue(0);

	QWidget::showEvent(event);
}

void OperationStatusPanel::UpdateProgressBar(int percentage)
{
	progressBar->setValue(percentage);
}

void OperationStatusPanel::HandleOperationStatus(OperationStatus status)
{
	switch (status)
	{
	case OperationStatus::LoadingScene:
		{
			progressBar->hide();
			operationStatusLabel->setText("Loading scene...");
		}
		break;
	case OperationStatus::RenderingScene:
		{
			operationStatusLabel->setText("Rendering scene...");
			progressBar->show();
		}
		break;
	case OperationStatus::WritingToFile:
		{
			progressBar->hide();
			operationStatusLabel->setText("Writing to file...");
		}
		break;
	default: operationStatusLabel->setText("Default...");
	}
}