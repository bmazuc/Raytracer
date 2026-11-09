#include "Raytracer.h"
#include "ExampleScenes/BasicScene.h"
#include "ExampleScenes/ComplexScene.h"
#include "Camera.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

#include <filesystem>

std::unique_ptr<Raytracer> CreateBasicScene(const RendererConfig& rendererConfig)
{
    CameraConfiguration cameraConfig;
    cameraConfig.imageWidth = 400;
    cameraConfig.aspectRatio = 16.0f / 9.0f;
    cameraConfig.samplesPerPixel = 100;
    cameraConfig.maxDepth = 50;

    cameraConfig.fov = 20;
    cameraConfig.position = Vec3(-2.0f, 2.0f, 1.0f);
    cameraConfig.lookAt = Vec3(0.0f, 0.0f, -1.0f);
    cameraConfig.vUp = Vec3(0.0f, 1.0f, 0.0f);

    cameraConfig.defocusAngle = 0.0f;
    cameraConfig.focusDistance = 10.0f;

    std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>(cameraConfig, rendererConfig);
    raytracer->SetScene(BasicScene::Create());

    return raytracer;
}

std::unique_ptr<Raytracer> CreateComplexScene(const RendererConfig& rendererConfig)
{
    CameraConfiguration cameraConfig;
    cameraConfig.imageWidth = 1200;
    cameraConfig.aspectRatio = 16.0f / 9.0f;
    cameraConfig.samplesPerPixel = 500;
    cameraConfig.maxDepth = 50;

    cameraConfig.fov = 20;
    cameraConfig.position = Vec3(13.0f, 2.0f, 3.0f);
    cameraConfig.lookAt = Vec3(0.0f, 0.0f, 0.0f);
    cameraConfig.vUp = Vec3(0.0f, 1.0f, 0.0f);

    cameraConfig.defocusAngle = 0.6f;
    cameraConfig.focusDistance = 10.0f;

    std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>(cameraConfig, rendererConfig);
    raytracer->SetScene(ComplexScene::Create());

    return raytracer;
}

int main(int argc, char* argv[])
{
    const char* outputFile = (argc > 1) ? argv[1] : "image.png";

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Raytracer");
    window.resize(1280, 720);

    QVBoxLayout* layout = new QVBoxLayout(&window);

    QPushButton* basicSceneRenderButton = new QPushButton("Basic Scene");
    QPushButton* complexSceneRenderButton = new QPushButton("Complex Scene");
    std::string deleteButtonText = "Delete " + std::string(outputFile);
    QPushButton* deleteButton = new QPushButton(deleteButtonText.c_str());

    layout->addWidget(basicSceneRenderButton);
    layout->addWidget(complexSceneRenderButton);
    layout->addWidget(deleteButton);

    QObject::connect(basicSceneRenderButton, &QPushButton::clicked, [&]()
        {
            basicSceneRenderButton->setEnabled(false);
            complexSceneRenderButton->setEnabled(false);
            deleteButton->setEnabled(false);

            RendererConfig rendererConfig;
            std::unique_ptr<Raytracer> raytracer = CreateBasicScene(rendererConfig);

            raytracer->RenderToFile(outputFile);

            basicSceneRenderButton->setEnabled(true);
            complexSceneRenderButton->setEnabled(true);
            deleteButton->setEnabled(true);
        });

    QObject::connect(complexSceneRenderButton, &QPushButton::clicked, [&]()
        {
            basicSceneRenderButton->setEnabled(false);
            complexSceneRenderButton->setEnabled(false);
            deleteButton->setEnabled(false);

            RendererConfig rendererConfig;
            std::unique_ptr<Raytracer> raytracer = CreateComplexScene(rendererConfig);

            raytracer->RenderToFile(outputFile);

            basicSceneRenderButton->setEnabled(true);
            complexSceneRenderButton->setEnabled(true);
            deleteButton->setEnabled(true);
        });

    QObject::connect(deleteButton, &QPushButton::clicked, [&]()
        {
            basicSceneRenderButton->setEnabled(false);
            complexSceneRenderButton->setEnabled(false);
            deleteButton->setEnabled(false);

            std::filesystem::remove(outputFile);

            basicSceneRenderButton->setEnabled(true);
            complexSceneRenderButton->setEnabled(true);
            deleteButton->setEnabled(true);
        });
    window.show();

    return app.exec();

	return 0;
}
