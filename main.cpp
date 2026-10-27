#include "Raytracer.h"
#include "Camera.h"
#include "ExampleScene.h"

using namespace std;

int main()
{
	Raytracer* raytracer = new Raytracer();

	Camera* camera = new Camera(400, 16.0f / 9.0f);

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
