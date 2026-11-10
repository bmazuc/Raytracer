#include "Panel/RenderPanel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

RenderPanel::RenderPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void RenderPanel::SetupUI()
{
	// Buttons
	renderButton = new QPushButton("Render", this);
	cancelButton = new QPushButton("Cancel", this);
	cancelButton->setEnabled(false);

	renderButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// layout
	QHBoxLayout* mainLayout = new QHBoxLayout(this);

	mainLayout->addWidget(renderButton, 1);
	mainLayout->addWidget(cancelButton, 1);
}

void RenderPanel::SetupConnections()
{
	connect(renderButton, &QPushButton::clicked,
		this, [this]()
		{
			cancelButton->setEnabled(true);
			renderButton->setEnabled(false);

			emit RenderRequested();
		});

	connect(cancelButton, &QPushButton::clicked,
		this, [this]()
		{
			emit CancelRequested();
		});
}

void RenderPanel::OnRenderEnded()
{
	cancelButton->setEnabled(false);
	renderButton->setEnabled(true);
}