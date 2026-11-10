#include "Panel/RenderPanel.h"

#include <QHBoxLayout>
#include <QPushButton>

RenderPanel::RenderPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void RenderPanel::SetupUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout(this);

	// Buttons
	renderButton = new QPushButton("Render", this);
	cancelButton = new QPushButton("Cancel", this);

	renderButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// layout
	mainLayout->addWidget(renderButton, 1);
	mainLayout->addWidget(cancelButton, 1);

	setLayout(mainLayout);
}

void RenderPanel::SetupConnections()
{
	connect(renderButton, &QPushButton::clicked,
		this, &RenderPanel::RenderRequested);

	connect(cancelButton, &QPushButton::clicked,
		this, &RenderPanel::CancelRequested);
}