#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene/Scene.h"
#include "Maths/Maths.h"
#include "Image/ImageBuffer.h"
#include "ThreadPool.h"
#include "Tile.h"

#include <iostream>
#include <future>
#include <iomanip>

Renderer::Renderer(const RendererConfig& config)
{
    tileSize = config.tileSize;
    threadCount = config.threadCount;
    progressMonitorFrequency = config.progressMonitorFrequency;
}

ImageBuffer Renderer::Render(const Camera& camera, const Scene& scene, const std::string fileName) const
{
    int width = camera.GetImageWidth();
    int height = camera.GetImageHeight();

    ImageBuffer imageBuffer(width, height);

    std::vector<Tile> tiles = GenerateTiles(width, height, tileSize);

    if (threadCount <= 1)
    {
        RenderSingleThread(camera, scene, imageBuffer, tiles);
    }
    else
    {
        RenderMultiThread(camera, scene, imageBuffer, tiles, threadCount);
    }

    return imageBuffer;
}

void Renderer::RenderSingleThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles) const
{
    RenderProgress renderProgress;
    renderProgress.tileCount = tiles.size();

    for (const Tile& tile : tiles)
    {
        RenderTile(tile, camera, scene, imageBuffer);

        ++renderProgress.completedTiles;

        DisplayProgress(renderProgress);
    }
}

void Renderer::RenderMultiThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, size_t threadCount) const
{
    RenderProgress renderProgress;
    renderProgress.tileCount = tiles.size();

    ThreadPool threadPool(std::max<size_t>(1, threadCount - 1));
    
    std::vector<std::future<void>> futures;
    futures.reserve(tiles.size());

    // Work distribution
    for (const Tile& tile : tiles)
    {
        futures.emplace_back(
            threadPool.Enqueue([&, tile]()
                {
                    RenderTile(
                        tile,
                        camera,
                        scene,
                        imageBuffer
                    );

                    renderProgress.completedTiles.fetch_add(1, std::memory_order_relaxed);
                })
        );
    }

    while (renderProgress.completedTiles.load(std::memory_order_relaxed) < renderProgress.tileCount)
    {
        DisplayProgress(renderProgress);

       std::this_thread::sleep_for(std::chrono::milliseconds(progressMonitorFrequency));
    }

    // Get eventual exceptions
    for (std::future<void>& future : futures)
    {
        future.get();
    }

    DisplayProgress(renderProgress);
}

void Renderer::RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer) const
{
    for (int y = tile.y; y < tile.y + tile.height; ++y)
    {
        for (int x = tile.x; x < tile.x + tile.width; ++x)
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

            imageBuffer.SetPixel(x, y, pixelColor);
        }
    }
}

void Renderer::DisplayProgress(const RenderProgress& progress) const
{
    const unsigned int completed = progress.completedTiles.load(std::memory_order_relaxed);
    const float percentage = progress.tileCount > 0 ? 100.0f * completed / progress.tileCount : 100.0f;

    std::clog << "\rRendering: " << std::fixed << std::setprecision(1) << percentage << '%' << std::flush;
}