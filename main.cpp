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
