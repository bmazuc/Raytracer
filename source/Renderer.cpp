#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene.h"
#include "Maths/Maths.h"

#include <iostream>

void Raytracer::Render(Camera* camera, Scene* scene, bool useAntiAliasing)
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
           Color pixelColor(0.0f, 0.0f, 0.0f);

           if (useAntiAliasing)
           {
               std::vector<Ray> samples = camera->GetRaySamplesForPixel(x, y);
               for (Ray& sample : samples)
               {
                   pixelColor += scene->GetPixelColor(sample, camera->GetMaxDepth());
               }
           }
           else
           {
               Ray ray = camera->ViewportPointToRay(x, y);
               pixelColor = scene->GetPixelColor(ray, camera->GetMaxDepth());
           }

           WriteColor(camera->GetPixelSamplesScale() * pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}

float Raytracer::LinearToGamma(float linear)
{
    if (linear > 0)
    {
        return std::sqrt(linear);
    }
    else
    {
        return 0;
    }
}

void Raytracer::WriteColor(Color color)
{
    float r = LinearToGamma(color.r);
    float g = LinearToGamma(color.g);
    float b = LinearToGamma(color.b);

    // Translate the [0,1] component values to the byte range [0,255].
    const Interval intensity(0.000f, 0.999f);
    int rbyte = int(255.999f * intensity.Clamp(r));
    int gbyte = int(255.999f * intensity.Clamp(g));
    int bbyte = int(255.999f * intensity.Clamp(b));

    // Write out the pixel color components.
    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}