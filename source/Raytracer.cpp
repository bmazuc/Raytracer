#include "Raytracer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene.h"
#include "Maths/Maths.h"

#include <iostream>

void Raytracer::Render(Camera* camera, Scene* scene)
{
    if (!camera || !scene)
    {
        return;
    }

    int width = camera->GetImageWidth();
    int height = camera->GetImageHeight();

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int y = 0; y < height; ++y)
    {
        std::clog << "\rScanlines remaining: " << (height - y) << ' ' << std::flush;
        for (int x = 0; x < width; ++x)
        {
            Ray ray = camera->ViewportPointToRay(x, y);
            Color pixelColor = scene->GetPixelColor(ray);
            WriteColor(pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}

void Raytracer::WriteColor(Color color)
{
    // Translate the [0,1] component values to the byte range [0,255].
    const Interval intensity(0.000f, 0.999f);
    int rbyte = int(255.999f * intensity.Clamp(color.r));
    int gbyte = int(255.999f * intensity.Clamp(color.g));
    int bbyte = int(255.999f * intensity.Clamp(color.b));

    // Write out the pixel color components.
    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}