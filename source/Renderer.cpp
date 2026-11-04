#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Scene/Scene.h"
#include "Maths/Maths.h"
#include "PPMWriter.h"
#include "FrameBuffer.h"
#include "ThreadPool.h"
#include "Tile.h"

#include <iostream>
#include <future>

Renderer::Renderer(int inTileSize, size_t inThreadCount, int inProgressMonitorFrequency)
    : tileSize(inTileSize), threadCount(inThreadCount), progressMonitorFrequency(inProgressMonitorFrequency)
{
}

void Renderer::Render(const Camera& camera, const Scene& scene, const PPMWriter& ppmWriter) const
{
    std::clog << "\033[?25l" << std::flush; // Hide command prompt cursor

    int width = camera.GetImageWidth();
    int height = camera.GetImageHeight();

    FrameBuffer framebuffer(width, height);

    ThreadPool threadPool(std::max<size_t>(1, threadCount - 1));

    std::vector<Tile> tiles = GenerateTiles(width, height, tileSize);
    tileCount = static_cast<unsigned int>(tiles.size());

    std::thread progressThread = std::thread(&Renderer::ProgressMonitor, this);

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
                        framebuffer
                    );
                })
            );
    }

    // Wait for render end
    for (auto& future : futures)
    {
        future.get();
    }

    renderingDone.store(true, std::memory_order_relaxed);
    progressThread.join();

    // Write ppm
    ppmWriter.Write(framebuffer);

    std::clog << "\rDone.                 \n";

    std::clog << "\033[?25h" << std::flush; // Show command prompt cursor
}

void Renderer::RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, FrameBuffer& frameBuffer) const
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

            frameBuffer.SetPixel(x, y, pixelColor);
        }
    }

    completedTiles.fetch_add(1, std::memory_order_relaxed);
}

void Renderer::ProgressMonitor() const
{
    while (!renderingDone.load(std::memory_order_relaxed))
    {
        std::unique_lock<std::mutex> lock(progressMutex);
        
        std::clog << "\rRendering: " << ((completedTiles.load(std::memory_order_relaxed)*100) / tileCount) << '%' << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(progressMonitorFrequency));
    }
}