#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

struct Color;
class Scene;
class Camera;
class PPMWriter;
struct Tile;
class FrameBuffer;

#include <thread>
#include <atomic>
#include <mutex>

class Renderer
{
public:
	// For the thread count, if using the max hardware concurrency, one of them will be use for progress monitoring and if not using max, we will use one more.
	// To improve, manage this cases
	Renderer(int inTileSize = 32, size_t inThreadCount = std::thread::hardware_concurrency(), int inProgressMonitorFrequency = 100);

	void Render(const Camera& camera, const Scene& scene, const PPMWriter& ppmWriter) const;

	void UseAntialising(bool newState) { useAntiAliasing = newState; }

private:
	void RenderTile(const Tile& tile, const Camera& camera, const Scene& scene, FrameBuffer& frameBuffer) const;
	void ProgressMonitor() const;

	bool useAntiAliasing = true;

	int tileSize;
	size_t threadCount;

	mutable std::mutex progressMutex;

	mutable unsigned int tileCount;
	mutable std::atomic<unsigned int> completedTiles = 0;

	mutable std::atomic<bool> renderingDone = false;

	int progressMonitorFrequency;
};

#endif // __RENDERER_H_INCLUDED__