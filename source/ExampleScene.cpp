#include "ExampleScene.h"
#include "Sphere.h"

void ExampleScene::InternalCreate()
{
	Add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
	Add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));
}