#ifndef __COMPLEX_SCENE_H_INCLUDED__
#define __COMPLEX_SCENE_H_INCLUDED__

#include "Scene/Scene.h"
#include "Scene/Sky/GradientSky.h"
#include "Scene/Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "Maths/Maths.h"

class ComplexScene
{
public:
    static std::unique_ptr<Scene> Create()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();

        std::unique_ptr<GradientSky> sky = std::make_unique<GradientSky>(Color(1.0f, 1.0f, 1.0f), Color(0.5f, 0.7f, 1.0f));
        scene->SetSky(std::move(sky));

        std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
        scene->Add(std::make_shared<Sphere>(Vec3(0.0f, -1000.0f, -1.0f), 1000.f, materialGround));

        for (int a = -11; a < 11; ++a)
        {
            for (int b = -11; b < 11; ++b)
            {
                float chooseMat = maths::Random();
                Vec3 position(a + 0.9f * maths::Random(), 0.2f, b + 0.9f * maths::Random());

                if ((position - Vec3(4.0f, 0.2f, 0.0f)).Length() > 0.9)
                {
                    std::shared_ptr<Material> sphereMaterial;

                    if (chooseMat < 0.8)
                    {
                        // diffuse
                        Color albedo = Color::Random() * Color::Random();
                        sphereMaterial = std::make_shared<Lambertian>(albedo);

                    }
                    else if (chooseMat < 0.95)
                    {
                        // metal
                        auto albedo = Color::Random(0.5f, 1.0f);
                        float roughness = maths::Random(0.0f, 0.5f);
                        sphereMaterial = std::make_shared<Metal>(albedo, roughness);
                    }
                    else
                    {
                        // glass
                        sphereMaterial = std::make_shared<Dielectric>(1.5f);
                    }

                    scene->Add(std::make_shared<Sphere>(position, 0.2f, sphereMaterial));
                }
            }
        }

        std::shared_ptr<Dielectric> material1 = std::make_shared<Dielectric>(1.5f);
        scene->Add(std::make_shared<Sphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));

        std::shared_ptr<Lambertian> material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
        scene->Add(std::make_shared<Sphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

        std::shared_ptr<Metal> material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        scene->Add(std::make_shared<Sphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));


        return scene;
    }
};

#endif // __COMPLEX_SCENE_H_INCLUDED__