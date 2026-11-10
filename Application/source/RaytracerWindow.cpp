#include "RaytracerWindow.h"
#include "Controller/RenderController.h"
#include "Panel/RenderPanel.h"
#include "Panel/OutputPanel.h"
#include "Panel/RenderParameterPanel.h"
#include "Panel/OperationStatusPanel.h"
#include "Raytracer.h"
#include "ImageView.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QCloseEvent>

RaytracerWindow::RaytracerWindow(std::string name, int w, int h, QWidget* parent)
	: QMainWindow(parent)
{
	renderController = new RenderController(this);

    SetupUI();
    SetupConnections();
    ApplyStyle();

    setWindowTitle(name.c_str());
    resize(w, h);
}

void RaytracerWindow::closeEvent(QCloseEvent* event)
{
    renderController->StopRender();
    event->accept();
}

void RaytracerWindow::SetupUI()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    renderParameterPanel = new RenderParameterPanel(centralWidget);
    renderParameterPanel->AddScene("Basic scene", 0);
    renderParameterPanel->AddScene("Complex scene", 1);

    imageView = new ImageView(centralWidget);

    renderPanel = new RenderPanel(centralWidget);
    outputPanel = new OutputPanel(centralWidget);

    operationStatusPanel = new OperationStatusPanel(centralWidget);
    operationStatusPanel->hide();

    QVBoxLayout* sideLayout = new QVBoxLayout();
    QVBoxLayout* rightSideLayout = new QVBoxLayout();

    setCentralWidget(centralWidget);

    sideLayout->addWidget(outputPanel, 1);
    sideLayout->addWidget(renderParameterPanel, 1);
    sideLayout->addWidget(renderPanel, 1);

    rightSideLayout->addWidget(imageView, 6);
    rightSideLayout->addWidget(operationStatusPanel, 1);

    mainLayout->addLayout(sideLayout, 1);
    mainLayout->addLayout(rightSideLayout, 4);
}

void RaytracerWindow::SetupConnections()
{
    connect(renderController, &RenderController::ProgressChanged, operationStatusPanel, &OperationStatusPanel::UpdateProgressBar);

    connect(renderPanel, &RenderPanel::RenderRequested,
        this, [this]()
        {
            operationStatusPanel->show();
            renderController->StartRender(renderParameterPanel->GetSceneIndex(), renderParameterPanel->GenerateRendererConfig(), outputPanel->GenerateOutputConfig());
        });

    connect(renderPanel, &RenderPanel::CancelRequested,
        this, [this]()
        {
            renderController->StopRender();
        });

    connect(renderController, &RenderController::ImageReady, imageView, &ImageView::SetImage);

    connect(renderController, &RenderController::OperationStatusChanged, operationStatusPanel, &OperationStatusPanel::HandleOperationStatus);

    connect(renderController, &RenderController::RenderFinished, renderPanel, &RenderPanel::OnRenderEnded);
    connect(renderController, &RenderController::RenderError, renderPanel, &RenderPanel::OnRenderEnded);
    connect(renderController, &RenderController::RenderCancelled, renderPanel, &RenderPanel::OnRenderEnded);

    connect(renderController, &RenderController::RenderFinished, operationStatusPanel, &QWidget::hide);
    connect(renderController, &RenderController::RenderError, operationStatusPanel, &QWidget::hide);
    connect(renderController, &RenderController::RenderCancelled, operationStatusPanel, &QWidget::hide);
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