#include "Panel/RenderPanel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>

RenderPanel::RenderPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void RenderPanel::SetupUI()
{
	// Progress bar
	progressBar = new QProgressBar(this);
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
	progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Buttons
	renderButton = new QPushButton("Render", this);
	cancelButton = new QPushButton("Cancel", this);
	cancelButton->setEnabled(false);

	renderButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* buttonLayout = new QHBoxLayout();

	mainLayout->addWidget(progressBar, 1);

	buttonLayout->addWidget(renderButton, 1);
	buttonLayout->addWidget(cancelButton, 1);
	mainLayout->addLayout(buttonLayout, 1);
}

void RenderPanel::SetupConnections()
{
	connect(renderButton, &QPushButton::clicked,
		this, [this]()
		{
			cancelButton->setEnabled(true);
			renderButton->setEnabled(false);

			QApplication::setOverrideCursor(Qt::BusyCursor);
			UpdateProgressBar(0);
			emit RenderRequested();
		});

	connect(cancelButton, &QPushButton::clicked,
		this, [this]()
		{
			UpdateProgressBar(0);
			emit CancelRequested();
		});
}

void RenderPanel::UpdateProgressBar(int percentage)
{
	progressBar->setValue(percentage);
}

void RenderPanel::OnRenderEnded()
{
	QApplication::restoreOverrideCursor();
	cancelButton->setEnabled(false);
	renderButton->setEnabled(true);
}