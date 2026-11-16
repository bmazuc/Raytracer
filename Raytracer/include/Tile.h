#ifndef RAYTRACER_TILE_H
#define RAYTRACER_TILE_H

#include <vector>

/**
 * Represents a rectangular region of an image.
 * 
 * Used to divide the rendering workload into smaller regions
 * that can be processed independently, including in parallel.
 */ 
struct Tile
{
public:
	int x;
	int y;

	size_t width;
	size_t height;
};

/**
 * Generates a collection of tiles covering the entire image,
 * using independent width and height.
 */
static std::vector<Tile> GenerateTiles(size_t imageWidth, size_t imageHeight,
	size_t tileSizeX, size_t tileSizeY)
{
	std::vector<Tile> tiles;

	for (size_t y = 0; y < imageHeight; y += tileSizeY)
	{
		for (size_t x = 0; x < imageWidth; x += tileSizeX)
		{
			tiles.push_back({
					static_cast<int>(x),
					static_cast<int>(y),
					std::min(tileSizeX, imageWidth - x),
					std::min(tileSizeY, imageHeight - y)
				});
		}
	}

	return tiles;
}

/**
 * Generates a collection of tiles covering the entire image,
 * using square dimensions.
 */
static std::vector<Tile> GenerateTiles(size_t imageWidth, size_t imageHeight,
	size_t tileSize)
{
	return GenerateTiles(imageWidth, imageHeight, tileSize, tileSize);
}

#endif // RAYTRACER_TILE_H