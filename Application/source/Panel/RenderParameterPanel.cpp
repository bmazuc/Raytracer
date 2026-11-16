#include "Panel/RenderParameterPanel.h"
#include "Renderer.h"
#include "UI/LayoutHelper.h"
#include "PositiveIntValidator.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QIntValidator>
#include <QGroupBox>
#include <QFormLayout>

QString RenderParameterPanel::GetGroupTitle() const
{
	return "Render Parameter";
}

void RenderParameterPanel::SetupUI()
{
	QFormLayout* formLayout = new QFormLayout();
	LayoutHelper::SetupFormLayout(formLayout);

	// thread count slider block
	QHBoxLayout* threadCountLayout = new QHBoxLayout();

	threadCountSlider = new QSlider(groupBox);
	threadCountSlider->setOrientation(Qt::Horizontal);
	// Max thread take main thread and render worker thread into account
	unsigned int maxThread = std::max(1u, ThreadUtils::GetMaxThreadAvailable() - 1u);
	threadCountSlider->setRange(1, maxThread);
	threadCountSlider->setValue(maxThread);

	threadCountSliderValueLabel = new QLabel(QString::number(maxThread), groupBox);
	threadCountSliderValueLabel->setAlignment(Qt::AlignRight);
	threadCountSliderValueLabel->setMinimumWidth(25);
	
	threadCountLayout->addWidget(threadCountSlider);
	threadCountLayout->addWidget(threadCountSliderValueLabel);

	formLayout->addRow("Thread count", threadCountLayout);

	// progressMonitorFrequency edit block

	progressMonitorFrequencyEdit = new QLineEdit(groupBox);
	progressMonitorFrequencyEdit->setValidator(new PositiveIntValidator(0));
	progressMonitorFrequencyEdit->setText("100");
	progressMonitorFrequencyEdit->setMinimumWidth(90);

	formLayout->addRow("Progress monitor frequency", progressMonitorFrequencyEdit);

	// tile size edit block

	tileSizeEdit = new QLineEdit(groupBox);
	tileSizeEdit->setValidator(new PositiveIntValidator(1));
	tileSizeEdit->setText("32");
	tileSizeEdit->setMinimumWidth(90);

	formLayout->addRow("Tile Length", tileSizeEdit);
	
	groupLayout->addLayout(formLayout);
}

void RenderParameterPanel::SetupConnections()
{
	connect(threadCountSlider, &QSlider::valueChanged,
		this, [this](int value)
		{
			threadCountSliderValueLabel->setText(QString::number(value));
		});
}

RendererConfiguration RenderParameterPanel::GenerateRendererConfig()
{
	RendererConfiguration config;
	config.tileSize = tileSizeEdit->text().toInt();
	config.progressMonitorFrequency = progressMonitorFrequencyEdit->text().toInt();
	config.threadCount = threadCountSlider->value();
	return config;
}