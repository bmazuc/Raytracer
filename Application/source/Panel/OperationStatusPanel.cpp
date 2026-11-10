#include "Panel/OperationStatusPanel.h"
#include "Raytracer.h"

#include <QProgressBar>
#include <QHBoxLayout>
#include <QLabel>

OperationStatusPanel::OperationStatusPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
}

void OperationStatusPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	
	// UpperLayout
	QHBoxLayout* upperLayout = new QHBoxLayout();
	
	operationStatusLabel = new QLabel("", this);

	progressBar = new QProgressBar(this);
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
	progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	progressBar->hide();

	upperLayout->addWidget(operationStatusLabel, 1);
	upperLayout->addWidget(progressBar, 2);

	mainLayout->addLayout(upperLayout);

	// LowerLayout
	QHBoxLayout* lowerLayout = new QHBoxLayout();

	QProgressBar* busyBar = new QProgressBar(this);
	busyBar->setRange(0, 0);
	busyBar->setFixedWidth(100);

	lowerLayout->addStretch();
	lowerLayout->addWidget(busyBar);

	mainLayout->addLayout(lowerLayout);
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