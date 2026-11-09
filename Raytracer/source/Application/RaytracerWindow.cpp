#include "Application/RaytracerWindow.h"
#include "Application/Controller/RaytracerController.h"
#include "Application/RenderPanel.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QProgressBar>
#include <QComboBox>

RaytracerWindow::RaytracerWindow(QWidget* parent, std::string name, int w, int h)
	: QMainWindow(parent)
{
	raytracerController = new RaytracerController(this);

    SetupUI(name, w, h);
    SetupConnections();
    ApplyStyle();
}

void RaytracerWindow::SetupUI(std::string name, int w, int h)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    sceneSelector = new QComboBox(centralWidget);
    sceneSelector->addItem("Basic scene", 0);
    sceneSelector->addItem("Complex scene", 1);

    progressBar = new QProgressBar(centralWidget);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    renderPanel = new RenderPanel(centralWidget);

    setCentralWidget(centralWidget);

    mainLayout->addWidget(sceneSelector, 1);
    mainLayout->addWidget(progressBar, 1);
    mainLayout->addWidget(renderPanel, 1);

    setWindowTitle(name.c_str());
    resize(w, h);
}

void RaytracerWindow::SetupConnections()
{
    connect(raytracerController,
        &RaytracerController::ProgressChanged,
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
            raytracerController->StartRender(sceneSelector->currentData().toInt());
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
    )");


}