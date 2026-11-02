#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene/Scene.h"
#include "Maths/Maths.h"
#include "PPMWriter.h"

#include <iostream>

void Renderer::Render(const Camera& camera, const Scene& scene, const PPMWriter& ppmWriter) const
{
    int width = camera.GetImageWidth();
    int height = camera.GetImageHeight();

    ppmWriter.WriteHeader(width, height);

    for (int y = 0; y < height; ++y)
    {
        std::clog << "\rScanlines remaining: " << (height - y) << ' ' << std::flush;
        for (int x = 0; x < width; ++x)
        {
           Color pixelColor(0.0f, 0.0f, 0.0f);

           if (useAntiAliasing)
           {
               std::vector<Ray> samples = camera.GetRaySamplesForPixel(x, y);
               for (Ray& sample : samples)
               {
                   pixelColor += scene.GetPixelColor(sample, camera.GetMaxDepth());
               }
               pixelColor *= camera.GetPixelSamplesScale();
           }
           else
           {
               Ray ray = camera.ViewportPointToRay(x, y);
               pixelColor = scene.GetPixelColor(ray, camera.GetMaxDepth());
           }

           ppmWriter.WritePixel(pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}
