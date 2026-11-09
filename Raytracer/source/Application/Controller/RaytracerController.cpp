#include "Application/Controller/RaytracerController.h"
#include "Raytracer.h"
#include "ExampleScenes/BasicScene.h"
#include "ExampleScenes/ComplexScene.h"
#include "Camera.h"

#include <filesystem>

RaytracerController::RaytracerController(QObject* parent)
	: QObject(parent), outputFile("")
{
	raytracer = std::make_unique<Raytracer>();
}

void RaytracerController::StartRender(int sceneIdx)
{
    switch (sceneIdx)
    {
        case 0:
            RenderBasicScene();
            break;
        case 1:
            RenderComplexScene();
            break;
        default:break;
    }
}

void RaytracerController::RenderBasicScene()
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

    Camera* camera = raytracer->GetCamera();
    camera->SetCameraConfig(cameraConfig);
    raytracer->SetScene(BasicScene::Create());

    raytracer->RenderToFile(outputFile, [this](int percentage)
    {
        emit ProgressChanged(percentage);
    });
}

void RaytracerController::RenderComplexScene()
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

    Camera* camera = raytracer->GetCamera();
    camera->SetCameraConfig(cameraConfig);
    raytracer->SetScene(ComplexScene::Create());

    raytracer->RenderToFile(outputFile, [this](int percentage)
        {
            emit ProgressChanged(percentage);
        });
}

void RaytracerController::DeleteImage()
{
    std::filesystem::remove(outputFile);
}