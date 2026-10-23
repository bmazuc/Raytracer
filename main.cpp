#include "Raytracer.h"

using namespace std;

int main()
{
	Raytracer* raytracer = new Raytracer();

	raytracer->Init(400, 16.0f / 9.0f);
	raytracer->Run();

	delete raytracer;
	raytracer = nullptr;

	return 0;
}
