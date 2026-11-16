#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene/Scene.h"
#include "Maths/MathsUtils.h"
#include "Image/ImageBuffer.h"
#include "ThreadPool.h"
#include "Tile.h"
#include "Utils/Log.h"

#include <iostream>
#include <future>
#include <iomanip>

void RendererConfig::Sanitize()
{
    if (!std::isfinite(tileSize) || tileSize == 0)
    {
        Log::Warning("Renderer : Tile size == " + std::to_string(tileSize) + " is invalid. Using 1 instead.");
        tileSize = 1;
    }

    if (!std::isfinite(threadCount) || threadCount == 0)
    {
        Log::Warning("Renderer : Thread count == " + std::to_string(tileSize) + " is invalid. Using 1 instead.");
        threadCount = 1;
    }
}

Renderer::Renderer(const RendererConfig& config)
{
    SetRendererConfig(config);
}

void Renderer::SetRendererConfig(const RendererConfig& config)
{
    configuration = config;
    configuration.Sanitize();
}

ImageBuffer Renderer::Render(const Camera& camera, const Scene& scene, const std::string fileName, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const
{
    size_t width = camera.GetImageWidth();
    size_t height = camera.GetImageHeight();

    ImageBuffer imageBuffer(width, height);

    std::vector<Tile> tiles = GenerateTiles(width, height, configuration.tileSize);

    if (configuration.threadCount <= 1)
    {
        RenderSingleThread(camera, scene, imageBuffer, tiles, callback, cancelRequested);
    }
    else
    {
        RenderMultiThread(camera, scene, imageBuffer, tiles, configuration.threadCount, callback, cancelRequested);
    }

    return imageBuffer;
}

void Renderer::RenderSingleThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const
{
    RenderProgress renderProgress;
    renderProgress.tileCount = tiles.size();

    for (const Tile& tile : tiles)
    {
        if (cancelRequested)
        {
            return;
        }

        RenderTile(tile, camera, scene, imageBuffer, cancelRequested);

        ++renderProgress.completedTiles;

        ReportProgress(renderProgress, callback);
    }
}

void Renderer::RenderMultiThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, size_t threadCount, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const
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
                    try
                    {
                        RenderTile(tile, camera, scene, imageBuffer, cancelRequested);
                    }
                    catch (...)
                    {
                        /*
                         * Every submitted tile must be accounted for, even on failure,
                         * otherwise the progress loop could wait forever.
                         */
                        renderProgress.completedTiles.fetch_add(1, std::memory_order_relaxed);
                        throw; // packaged_task stores the exception in its future.
                    }

                    renderProgress.completedTiles.fetch_add(1, std::memory_order_relaxed);
                })
        );
    }

    while (renderProgress.completedTiles.load(std::memory_order_relaxed) < renderProgress.tileCount)
    {
       if (cancelRequested.load())
       {
           return;
       }

       ReportProgress(renderProgress, callback);

       std::this_thread::sleep_for(std::chrono::milliseconds(configuration.progressMonitorFrequency));
    }

    /**
     * Retrieve every future so all tasks are joined and all stored exceptions
     * are observed. Rethrow the first failure after checking the remaining tasks.
     */
    std::exception_ptr firstException;
    for (std::future<void>& future : futures)
    {
        try
        {
            future.get();
        }
        catch (...)
        {
            if (!firstException)
            {
                firstException = std::current_exception();
            }
        }
    }

    if (!cancelRequested.load())
    {
        ReportProgress(renderProgress, callback);
    }

    if (firstException)
    {
        std::rethrow_exception(firstException);
    }
}

void Renderer::RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::atomic_bool& cancelRequested) const
{
    for (int y = tile.y; y < tile.y + tile.height; ++y)
    {
        for (int x = tile.x; x < tile.x + tile.width; ++x)
        {
            if (cancelRequested.load())
            {
                return;
            }

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

void Renderer::ReportProgress(const RenderProgress& progress, const ProgressCallback& callback) const
{
    const size_t completed = progress.completedTiles.load(std::memory_order_relaxed);
    const float percentage = progress.tileCount > 0 ? 100.0f * completed / progress.tileCount : 100.0f;

    if (callback)
    {
        callback(percentage);
    }
}