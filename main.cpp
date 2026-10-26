#include "Raytracer.h"
#include "ExampleScene.h"

using namespace std;

int main()
{
	Raytracer* raytracer = new Raytracer(400, 16.0f / 9.0f);

	raytracer->SetScene(new ExampleScene());

	raytracer->Run();

	delete raytracer;
	raytracer = nullptr;

	return 0;
}
