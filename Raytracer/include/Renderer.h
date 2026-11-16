#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H

#include "Utils/ThreadUtils.h"

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
	// Total number of tiles in the current render
	size_t tileCount = 0;
	// Number of completed tiles, updated by rendering workers
	std::atomic<size_t> completedTiles = { 0 };
};

/**
 * Stores the configuration parameters controlling
 * the rendering process.
 */
struct RendererConfiguration
{
public:
	// Width and height, in pixels, of square rendering tiles
	int tileSize = 32;
	// Maximum number of renderer threads requested for tile processing
	size_t threadCount = ThreadUtils::GetMaxThreadAvailable();
	// Delay in milliseconds between progress checks in multithreaded rendering
	unsigned int progressMonitorFrequency = 100;

	/**
	 * Check and modify incorrect parameters.
	 */
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
	/**
	 * Initializes the renderer using the provided configuration.
	 *
	 * Sets up the rendering parameters used to control
	 * tile processing, thread allocation and progress monitoring.
	 *
	 * @param config Initial renderer configuration.
	 */
	Renderer(const RendererConfiguration& config);

	void SetRendererConfiguration(const RendererConfiguration& config);

	/**
	 * Renders a scene using the specified camera and configuration.
	 *
	 * Distributes the rendering workload across image tiles and
	 * returns the resulting image buffer.
	 *
	 * Supports progress reporting and cancellation through callbacks
	 * and an atomic cancellation flag.
	 *
	 * @param camera Camera used to generate rendering rays.
	 * @param scene Scene to render.
	 * @param fileName Name associated with the rendering operation.
	 * @param callback Callback used to report rendering progress.
	 * @param cancelRequested Atomic flag indicating whether rendering
	 * should be cancelled.
	 * @return The resulting rendered image buffer.
	*/
	ImageBuffer Render(const Camera& camera, const Scene& scene, const std::string fileName, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const;

	/**
	 *  Enables or disables anti-aliasing during rendering.
	 *
	 * @param newState True to enable anti-aliasing, false otherwise.
	 */
	void UseAntialising(bool newState) { useAntiAliasing = newState; }

private:
	/**
	 * Processes each tile on the calling thread and checks
	 * for cancellation between rendering operations.
	 */
	void RenderSingleThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const;
	/**
	 * Distributes image tiles across multiple worker threads.
	 *
	 * Coordinates parallel tile rendering and progress reporting
	 * until all tasks are completed or cancellation is requested.
	 *
	 * @param threadCount Number of worker threads to use.
	 */
	void RenderMultiThread(const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::vector<Tile>& tiles, size_t threadCount, const ProgressCallback& callback, const std::atomic_bool& cancelRequested) const;

	/**
	 * Renders the pixels contained within a tile.
	 *
	 * Generates camera rays, evaluates their contribution to each pixel
	 * and writes the resulting colors into the image buffer.
	 *
	 * @param tile Image region to render.
		 */
	void RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, ImageBuffer& imageBuffer, const std::atomic_bool& cancelRequested) const;
	/**
	 * Reports the current rendering progress.
	 *
	 * Computes the completion percentage from the total number
	 * of tiles and the number of completed tiles.
	 *
	 * @param progress Current rendering progress information.
	 * @param callback Callback used to notify the application.
	 */
	void ReportProgress(const RenderProgress& progress, const ProgressCallback& callback) const;

	// Enables multiple camera samples per pixel when true
	bool useAntiAliasing = true;

	// Rendering parameters used for the current render operation
	RendererConfiguration configuration;
};

#endif // RAYTRACER_RENDERER_H