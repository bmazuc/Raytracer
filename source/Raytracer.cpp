#include "Raytracer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene.h"
#include "Maths/Maths.h"

#include <iostream>

Raytracer::Raytracer(int inImageWidth, int inImageHeight)
    : width(inImageWidth), height(inImageHeight)
{
}

Raytracer::Raytracer(int inImageWidth, float aspectRatio)
    : width(inImageWidth)
{
    int computedImageHeight = int(inImageWidth / aspectRatio);
    if (computedImageHeight < 1)
    {
        computedImageHeight = 1;
    }

    height = computedImageHeight;
}

void Raytracer::Run()
{
    if (!scene)
    {
        return;
    }

    viewport = new Viewport(scene->GetCamera(), width, height);

    scene->Create();

    Render();
}

void Raytracer::Render()
{
    Camera* camera = scene->GetCamera();

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; ++j)
    {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i)
        {
            Vec3 rayDirection = viewport->GetPixelCenter(i, j) - camera->GetCenter();
            Ray ray(camera->GetCenter(), rayDirection);

            Color pixelColor = GetRayColor(ray);
            pixelColor.Write(std::cout);
        }
    }

    std::clog << "\rDone.                 \n";
}

Color Raytracer::GetRayColor(Ray ray)
{
    if (scene)
    {
        HitInfo hitInfo;
        if (scene->Hit(ray, Interval(0, maths::infinity), hitInfo))
        {
            return 0.5f * (
                Color(hitInfo.normal.x,
                    hitInfo.normal.y,
                    hitInfo.normal.z)
                + Color::white);
        }
    }

    Vec3 normalizeDirection = ray.direction.GetNormal();
    float a = 0.5f * (normalizeDirection.y + 1.0f);
    return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}

void Raytracer::SetScene(Scene* inScene)
{
    if (scene)
    {
        delete scene;
    }

    scene = inScene;
}

Raytracer::~Raytracer()
{
    if (viewport)
    {
        delete viewport;
        viewport = nullptr;
    }

    if (scene)
    {
        delete scene;
        scene = nullptr;
    }
}