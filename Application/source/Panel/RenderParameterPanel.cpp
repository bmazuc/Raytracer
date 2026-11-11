#include "Panel/RenderParameterPanel.h"
#include "Renderer.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QIntValidator>

RenderParameterPanel::RenderParameterPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void RenderParameterPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	// thread count slider block
	QHBoxLayout* threadCountLayout = new QHBoxLayout();
	QLabel* threadCountLabel = new QLabel("Thread count", this);
	threadCountSlider = new QSlider(this);
	threadCountSlider->setOrientation(Qt::Horizontal);
	unsigned int maxThread = std::max(1u, std::thread::hardware_concurrency() - 1);
	threadCountSlider->setRange(1, maxThread);
	threadCountSlider->setValue(maxThread);
	threadCountSliderValueLabel = new QLabel(QString::number(maxThread), this);
	threadCountLayout->addWidget(threadCountLabel);
	threadCountLayout->addWidget(threadCountSlider);
	threadCountLayout->addWidget(threadCountSliderValueLabel);

	QIntValidator* validator = new QIntValidator(this);

	// progressMonitorFrequency edit block
	QHBoxLayout* progressMonitorFrequencyLayout = new QHBoxLayout();
	QLabel* progressMonitorFrequencyLabel = new QLabel("Progress monitor frequency", this);
	progressMonitorFrequencyEdit = new QLineEdit(this);
	progressMonitorFrequencyEdit->setValidator(validator);
	progressMonitorFrequencyEdit->setText("100");
	progressMonitorFrequencyLayout->addWidget(progressMonitorFrequencyLabel);
	progressMonitorFrequencyLayout->addWidget(progressMonitorFrequencyEdit);

	// tile size edit block
	QHBoxLayout* tileSizeLayout = new QHBoxLayout();
	QLabel* tileSizeLabel = new QLabel("Tile Size", this);
	tileSizeEdit = new QLineEdit(this);
	tileSizeEdit->setValidator(validator);
	tileSizeEdit->setText("32");
	tileSizeLayout->addWidget(tileSizeLabel);
	tileSizeLayout->addWidget(tileSizeEdit);

	mainLayout->addLayout(threadCountLayout);
	mainLayout->addLayout(progressMonitorFrequencyLayout);
	mainLayout->addLayout(tileSizeLayout);
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