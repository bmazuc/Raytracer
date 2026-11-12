#include "RaytracerWindow.h"
#include "Controller/RenderController.h"
#include "Panel/RenderPanel.h"
#include "Panel/OutputPanel.h"
#include "Panel/RenderParameterPanel.h"
#include "Panel/SceneFilePanel.h"
#include "Panel/OperationStatusPanel.h"
#include "Raytracer.h"
#include "Panel/ImageViewPanel.h"

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

    imageViewPanel = new ImageViewPanel(centralWidget);

    renderPanel = new RenderPanel(centralWidget);
    outputPanel = new OutputPanel(centralWidget);

    operationStatusPanel = new OperationStatusPanel(centralWidget);
    operationStatusPanel->hide();

    // Left side

    QVBoxLayout* leftSideLayout = new QVBoxLayout();
    leftSideLayout->addWidget(outputPanel, 2);
    leftSideLayout->addWidget(renderParameterPanel, 2);
    leftSideLayout->addWidget(sceneFilePanel, 2);
    leftSideLayout->addWidget(renderPanel, 1);

    QWidget* leftSide = new QWidget();
    leftSide->setLayout(leftSideLayout);

    // Right side

    QVBoxLayout* rightSideLayout = new QVBoxLayout();
    rightSideLayout->addWidget(imageViewPanel, 6);
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

    connect(renderController, &RenderController::ImageReady, imageViewPanel, &ImageViewPanel::SetImage);

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

        QGroupBox {
            border: 1px solid #394354;
            border-radius: 6px;
            margin-top: 12px;
            padding-top: 8px;
            font-weight: bold;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
            color: #E5EAF2;
        }

        QPushButton {
            background-color: #3478D4;
            border: none;
            border-radius: 5px;
            padding: 8px 12px;
        }

        QPushButton:hover {
            background-color: #438FE8;
        }

        QPushButton:pressed {
            background-color: #2863B3;
        }

        QPushButton:disabled {
            background-color: #394354;
            color: #858D9A;
        }

        QPushButton#browseButton {
            padding: 3px 8px;
        }

		QLineEdit {
			color: #20242C;
            background-color: #F1F3F5;
            border: 1px solid #C5CAD2;
            border-radius: 3px;
            padding: 4px 6px;
            selection-background-color: #3478D4;
		}
QLineEdit:focus {
            border: 1px solid #438FE8;
        }

        QProgressBar {
            background-color: #252B36;
            border: 1px solid #465164;
            border-radius: 4px;
            text-align: center;
        }

        QProgressBar::chunk {
            background-color: #3478D4;
            border-radius: 3px;
        }

        QSlider::groove:horizontal {
            height: 4px;
            background: #465164;
            border-radius: 2px;
        }

        QSlider::handle:horizontal {
            background: #438FE8;
            width: 12px;
            margin: -5px 0;
            border-radius: 6px;
        }

        QSplitter::handle {
            background-color: #394354;
        }
    )");
}