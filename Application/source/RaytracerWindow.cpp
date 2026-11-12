#include "RaytracerWindow.h"
#include "Controller/RenderController.h"
#include "Panel/RenderPanel.h"
#include "Panel/OutputPanel.h"
#include "Panel/RenderParameterPanel.h"
#include "Panel/SceneFilePanel.h"
#include "Panel/OperationStatusPanel.h"
#include "Raytracer.h"
#include "ImageView.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QCloseEvent>
#include <QFileInfo>
#include <QMessageBox>
#include <QSplitter>

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

    renderParameterPanel = new RenderParameterPanel(centralWidget);
    sceneFilePanel = new SceneFilePanel(centralWidget);

    imageView = new ImageView(centralWidget);

    renderPanel = new RenderPanel(centralWidget);
    outputPanel = new OutputPanel(centralWidget);

    operationStatusPanel = new OperationStatusPanel(centralWidget);
    operationStatusPanel->hide();

    // Left side

    QVBoxLayout* leftSideLayout = new QVBoxLayout();
    leftSideLayout->addWidget(outputPanel, 1);
    leftSideLayout->addWidget(renderParameterPanel, 1);
    leftSideLayout->addWidget(sceneFilePanel, 1);
    leftSideLayout->addWidget(renderPanel, 1);

    QWidget* leftSide = new QWidget();
    leftSide->setLayout(leftSideLayout);

    // Right side

    QVBoxLayout* rightSideLayout = new QVBoxLayout();
    rightSideLayout->addWidget(imageView, 6);
    rightSideLayout->addWidget(operationStatusPanel, 1);

    QWidget* rightSide = new QWidget();
    rightSide->setLayout(rightSideLayout);

    // Horizontal splitter

    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);

    splitter->addWidget(leftSide);
    splitter->addWidget(rightSide);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);

    splitter->setSizes({ 300, 1200 });
    splitter->setHandleWidth(5);

    splitter->setChildrenCollapsible(false);

    // Main layout

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(splitter);

    setCentralWidget(centralWidget);
}

void RaytracerWindow::SetupConnections()
{
    connect(renderController, &RenderController::ProgressChanged, operationStatusPanel, &OperationStatusPanel::UpdateProgressBar);

    connect(renderPanel, &RenderPanel::RenderRequested,
        this, [this]()
        {
            const QString scenePath = sceneFilePanel->GetScenePath();
            const QFileInfo sceneInfo(scenePath);

            if (scenePath.isEmpty() || sceneInfo.suffix().compare("json", Qt::CaseInsensitive) != 0)
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Invalid scene");
                msgBox.setText("Please select a valid JSON scene before starting the render.");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setStandardButtons(QMessageBox::Ok);

                msgBox.setStyleSheet(
                    "QLabel {"
                    "    color: #222222;"
                    "}"
                );

                msgBox.exec();

                return;
            }

            renderPanel->OnRenderStart();

            operationStatusPanel->show();
            renderController->StartRender(sceneFilePanel->GetScenePath(), renderParameterPanel->GenerateRendererConfig(), outputPanel->GenerateOutputConfig());
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

        QGroupBox {
            border: 1px solid #444444;
            border-radius: 6px;
            margin-top: 12px;
            padding: 12px 8px 8px 8px;
            font-weight: bold;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
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
            font-size: 10pt;
            padding: 6px 10px;
            padding: 9px;
        }

        QPushButton:hover {
            background-color: #438FE8;
        }

        QPushButton#browseButton {
            padding: 2px 6px;
        }

		QLineEdit {
			color: black;
			background-color:white;
		}
    )");
}