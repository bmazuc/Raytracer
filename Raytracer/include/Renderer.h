#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

struct Color;
class Scene;
class Camera;
class PPMWriter;
struct Tile;
class ImageBuffer;

#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>

struct RenderProgress
{
public:
	size_t tileCount = 0;
	std::atomic<unsigned int> completedTiles = { 0 };
};

struct RendererConfig
{
public:
	int tileSize = 32;
	size_t threadCount = std::thread::hardware_concurrency();
	int progressMonitorFrequency = 100;
};

class Renderer
{
public:
	// For the thread count, if using the max hardware concurrency, one of them will be use for progress monitoring and if not using max, we will use one more.
	// To improve, manage this cases
	Renderer(const RendererConfig& config);

	ImageBuffer Render(const Camera& camera, const Scene& scene, const std::string fileName) const;

	void UseAntialising(bool newState) { useAntiAliasing = newState; }

private:
	void RenderSingleThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles) const;
	void RenderMultiThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, size_t threadCount) const;

	void RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer) const;
	void DisplayProgress(const RenderProgress& progress) const;

	bool useAntiAliasing = true;

	int tileSize;
	size_t threadCount;

	int progressMonitorFrequency;
};

#endif // RAYTRACER_RENDERER_H