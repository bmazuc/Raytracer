#include "Renderer.h"
#include "Camera.h"
#include "ExampleScene.h"

using namespace std;

int main()
{
	Raytracer* raytracer = new Raytracer();

	CameraConfiguration cameraConfig;
	cameraConfig.imageWidth = 400;
	cameraConfig.aspectRatio = 16.0f / 9.0f;
	cameraConfig.samplesPerPixel = 100;
	cameraConfig.maxDepth = 50;

	cameraConfig.fov = 20;
	cameraConfig.position = Vec3(-2.0f, 2.0f, 1.0f);
	cameraConfig.lookAt = Vec3(0.0f, 0.0f, -1.0f);
	cameraConfig.up = Vec3(0.0f, 1.0f, 0.0f);

	Camera* camera = new Camera(cameraConfig);

	ExampleScene* exampleScene = new ExampleScene();
	exampleScene->Create();

	raytracer->Render(camera, exampleScene);

	delete exampleScene;
	exampleScene = nullptr;

	delete camera;
	camera = nullptr;

	delete raytracer;
	raytracer = nullptr;

	return 0;
}
