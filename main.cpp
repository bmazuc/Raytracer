#include "Raytracer.h"
#include "ExampleScenes/BasicScene.h"
#include "ExampleScenes/ComplexScene.h"
#include "Camera.h"

std::unique_ptr<Raytracer> CreateBasicScene()
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

    std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>(cameraConfig);
    raytracer->SetScene(BasicScene::Create());

    return raytracer;
}

std::unique_ptr<Raytracer> CreateComplexScene()
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

    std::unique_ptr<Raytracer> raytracer = std::make_unique<Raytracer>(cameraConfig);
    raytracer->SetScene(ComplexScene::Create());

    return raytracer;
}

int main()
{
    std::unique_ptr<Raytracer> raytracer = CreateComplexScene();//CreateBasicScene();
	
    raytracer->Render();

	return 0;
}
