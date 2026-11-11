#include "Panel/RenderParameterPanel.h"
#include "Renderer.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QIntValidator>
#include <QGroupBox>
#include <QFormLayout>

RenderParameterPanel::RenderParameterPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void RenderParameterPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(10, 10, 10, 10);
	mainLayout->setSpacing(8);

	QGroupBox* groupBox = new QGroupBox("Render Parameter", this);
	QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

	QFormLayout* formLayout = new QFormLayout();

	// thread count slider block
	QHBoxLayout* threadCountLayout = new QHBoxLayout();

	threadCountSlider = new QSlider(groupBox);
	threadCountSlider->setOrientation(Qt::Horizontal);
	unsigned int maxThread = std::max(1u, std::thread::hardware_concurrency() - 1);
	threadCountSlider->setRange(1, maxThread);
	threadCountSlider->setValue(maxThread);

	threadCountSliderValueLabel = new QLabel(QString::number(maxThread), groupBox);
	threadCountLayout->addWidget(threadCountSlider);
	threadCountLayout->addWidget(threadCountSliderValueLabel);

	formLayout->addRow("Thread count", threadCountLayout);

	QIntValidator* validator = new QIntValidator(groupBox);

	// progressMonitorFrequency edit block
	
	progressMonitorFrequencyEdit = new QLineEdit(groupBox);
	progressMonitorFrequencyEdit->setValidator(validator);
	progressMonitorFrequencyEdit->setText("100");

	formLayout->addRow("Progress monitor frequency", progressMonitorFrequencyEdit);

	// tile size edit block

	tileSizeEdit = new QLineEdit(groupBox);
	tileSizeEdit->setValidator(validator);
	tileSizeEdit->setText("32");

	formLayout->addRow("Tile Size", tileSizeEdit);
	
	groupLayout->addStretch();
	groupLayout->addLayout(formLayout);
	groupLayout->addStretch();

	mainLayout->addWidget(groupBox);
}

void RenderParameterPanel::SetupConnections()
{
	connect(threadCountSlider, &QSlider::valueChanged,
		this, [this](int value)
		{
			threadCountSliderValueLabel->setText(QString::number(value));
		});
}

RendererConfig RenderParameterPanel::GenerateRendererConfig()
{
	RendererConfig config;
	config.tileSize = tileSizeEdit->text().toInt();
	config.progressMonitorFrequency = progressMonitorFrequencyEdit->text().toInt();
	config.threadCount = threadCountSlider->value();
	return config;
}