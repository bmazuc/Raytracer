#include "Raytracer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Sphere.h"

#include <iostream>

void Raytracer::Init(int inImageWidth, int inImageHeight)
{
    width = inImageWidth;
    height = inImageHeight;

    camera = new Camera();
    viewport = new Viewport(camera, width, height);
}

void Raytracer::Init(int inImageWidth, float aspectRatio)
{
    int computedImageHeight = int(inImageWidth / aspectRatio);
    if (computedImageHeight < 1)
    {
        computedImageHeight = 1;
    }

    Init(inImageWidth, computedImageHeight);
}

void Raytracer::Run()
{
    if (!viewport || !camera)
    {
        return;
    }

    sphere = new Sphere(Vec3(0, 0, -1), 0.5, Color::red);

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

    delete sphere;
    sphere = nullptr;
}

Color Raytracer::GetRayColor(Ray ray)
{
    if (sphere && sphere->IsHit(ray))
    {
        return sphere->GetColor();
    }

    Vec3 normalizeDirection = ray.direction.GetNormal();
    float a = 0.5f * (normalizeDirection.y + 1.0f);
    return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}

Raytracer::~Raytracer()
{
    if (camera)
    {
        delete camera;
        camera = nullptr;
    }

    if (viewport)
    {
        delete viewport;
        viewport = nullptr;
    }
}