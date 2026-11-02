#ifndef __BASIC_SCENE_H_INCLUDED__
#define __BASIC_SCENE_H_INCLUDED__

#include "Scene/Scene.h"
#include "Scene/Sky/GradientSky.h"
#include "Scene/Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

class BasicScene
{
public:
	static std::unique_ptr<Scene> Create()
	{
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();

        std::unique_ptr<GradientSky> sky = std::make_unique<GradientSky>(Color(1.0f, 1.0f, 1.0f), Color(0.5f, 0.7f, 1.0f));
        scene->SetSky(std::move(sky));

        std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
        std::shared_ptr<Lambertian> materialCenter = std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
        std::shared_ptr<Dielectric> materialLeft = std::make_shared<Dielectric>(1.50f);
        std::shared_ptr<Dielectric> materialBubble = std::make_shared<Dielectric>(1.00f / 1.50f);
        std::shared_ptr<Metal> materialRight = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 1.0f);

        scene->Add(std::make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
        scene->Add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.2f), 0.5f, materialCenter));
        scene->Add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
        scene->Add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.4f, materialBubble));
        scene->Add(std::make_shared<Sphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));

        return scene;
	}
};

#endif // __BASIC_SCENE_H_INCLUDED__