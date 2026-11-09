#include "Application/RaytracerWindow.h"
#include "Application/Controller/RenderController.h"
#include "Application/RenderPanel.h"
#include "Application/Panel/OutputPanel.h"
#include "Raytracer.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QProgressBar>
#include <QComboBox>
#include <QCloseEvent>

RaytracerWindow::RaytracerWindow(QWidget* parent, std::string name, int w, int h)
	: QMainWindow(parent)
{
	renderController = new RenderController(this);

    SetupUI(name, w, h);
    SetupConnections();
    ApplyStyle();
}

void RaytracerWindow::closeEvent(QCloseEvent* event)
{
    renderController->StopRender();
    event->accept();
}

void RaytracerWindow::SetupUI(std::string name, int w, int h)
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    sceneSelector = new QComboBox(centralWidget);
    sceneSelector->addItem("Basic scene", 0);
    sceneSelector->addItem("Complex scene", 1);
    sceneSelector->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    progressBar = new QProgressBar(centralWidget);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    renderPanel = new RenderPanel(centralWidget);
    outputPanel = new OutputPanel(centralWidget);

    QVBoxLayout* sideLayout = new QVBoxLayout();

    setCentralWidget(centralWidget);

    sideLayout->addWidget(outputPanel, 1);
    sideLayout->addWidget(sceneSelector, 1);
    sideLayout->addWidget(renderPanel, 1);

    mainLayout->addLayout(sideLayout);
    mainLayout->addWidget(progressBar, 4);

    setWindowTitle(name.c_str());
    resize(w, h);
}

void RaytracerWindow::SetupConnections()
{
    connect(renderController,
        &RenderController::ProgressChanged,
        this,
        [this](int percentage)
        {
            progressBar->setValue(percentage);
        });

    connect(renderPanel,
        &RenderPanel::RenderRequested,
        this,
        [this]()
        {
            progressBar->setValue(0);
            renderController->StartRender(sceneSelector->currentData().toInt(), outputPanel->GenerateOutputConfig());
        });

    connect(renderPanel,
        &RenderPanel::CancelRequested,
        this,
        [this]()
        {
            progressBar->setValue(0);
            renderController->StopRender();
        });
}

void RaytracerWindow::ApplyStyle()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #171B24;
        }

        QWidget {
            color: #E5EAF2;
            font-family: "Segoe UI";
            font-size: 10pt;
        }

        QPushButton {
            background-color: #3478D4;
            border: none;
            border-radius: 5px;
            padding: 9px;
        }

        QPushButton:hover {
            background-color: #438FE8;
        }

		QLineEdit {
			color: black;
			background-color:white;
		}
    )");
}