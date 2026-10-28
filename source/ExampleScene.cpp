#include "ExampleScene.h"
#include "Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "Color.h"

void ExampleScene::InternalCreate()
{
	std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
	std::shared_ptr<Lambertian> materialCenter = std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
	std::shared_ptr<Dielectric> materialLeft = std::make_shared<Dielectric>(1.50f);
	std::shared_ptr<Dielectric> materialBubble = std::make_shared<Dielectric>(1.00f/1.50f);
	std::shared_ptr<Metal> materialRight = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 1.0f);

	Add(std::make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.f, materialGround));
	Add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.2f), 0.5f, materialCenter));
	Add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
	Add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.4f, materialBubble));
	Add(std::make_shared<Sphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));
}