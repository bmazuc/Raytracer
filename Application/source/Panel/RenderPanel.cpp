#include "Panel/RenderPanel.h"
#include "UI/LayoutHelper.h"
#include "UI/UIConstants.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>


void RenderPanel::SetupUI()
{
	// Buttons
	renderButton = new QPushButton("Render", this);
	cancelButton = new QPushButton("Cancel", this);
	cancelButton->setEnabled(false);

	renderButton->setMinimumHeight(UIConstants::Dimensions::RenderButtonHeight);
	cancelButton->setMinimumHeight(UIConstants::Dimensions::RenderButtonHeight);

	renderButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	mainLayout->addWidget(renderButton, 1);
	mainLayout->addWidget(cancelButton, 1);
}

void RenderPanel::SetupConnections()
{
	connect(renderButton, &QPushButton::clicked,
		this, [this]()
		{
			emit RenderRequested();
		});

	connect(cancelButton, &QPushButton::clicked,
		this, [this]()
		{
			emit CancelRequested();
		});
}

void RenderPanel::OnRenderStart()
{
	cancelButton->setEnabled(true);
	renderButton->setEnabled(false);
}

void RenderPanel::OnRenderEnded()
{
	cancelButton->setEnabled(false);
	renderButton->setEnabled(true);
}