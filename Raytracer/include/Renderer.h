#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>
#include <functional>

struct Color;
class Scene;
class Camera;
class PPMWriter;
struct Tile;
class ImageBuffer;

/**
 * Tracks of the progress of the rendering operation.
 * 
 * Stores the total number of tiles and the number of tiles
 * successfully completed during rendering.
 */
struct RenderProgress
{
public:
	size_t tileCount = 0;
	std::atomic<size_t> completedTiles = { 0 };
};

/**
 * Stores the configuration parameters controlling
 * the rendering process.
 */
struct RendererConfig
{
public:
	int tileSize = 32;
	size_t threadCount = std::thread::hardware_concurrency();
	unsigned int progressMonitorFrequency = 100;

	void Sanitize();
};

/**
 * Progress callback allows to retrieve completion percentage
 * and use it elsewhere.
 */
using ProgressCallback = std::function<void(int)>;

/**
 * Coordinates the rendering of a 3D scene into an image buffer.
 * 
 * Divides the image into tiles and distributes the rendering workload
 * across one or multiple threads.
 */
class Renderer
{
public:
	Renderer(const RendererConfig& config);

	void SetRendererConfig(const RendererConfig& config);

	ImageBuffer Render(const Camera& camera, const Scene& scene, const std::string fileName, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const;

	void UseAntialising(bool newState) { useAntiAliasing = newState; }

private:
	void RenderSingleThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const;
	void RenderMultiThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, size_t threadCount, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const;

	void RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::atomic_bool& cancelRequested) const;
	void ReportProgress(const RenderProgress& progress, const ProgressCallback& callback) const;

	bool useAntiAliasing = true;

	RendererConfig configuration;
};

#endif // RAYTRACER_RENDERER_H