#include "Panel/OperationStatusPanel.h"
#include "Raytracer.h"
#include "UI/LayoutHelper.h"
#include "UI/UIConstants.h"

#include <QProgressBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

QString OperationStatusPanel::GetGroupTitle() const
{
	return "Operation Status";
}

void OperationStatusPanel::SetupUI()
{
	// UpperLayout
	QHBoxLayout* upperLayout = new QHBoxLayout();
	
	operationStatusLabel = new QLabel("", groupBox);

	progressBar = new QProgressBar(groupBox);
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
	progressBar->setMinimumHeight(UIConstants::Dimensions::ProgressBarHeight);
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
	busyBar->setMinimumHeight(UIConstants::Dimensions::ProgressBarHeight);

	lowerLayout->addStretch();
	lowerLayout->addWidget(busyBar);

	groupLayout->addLayout(lowerLayout);
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