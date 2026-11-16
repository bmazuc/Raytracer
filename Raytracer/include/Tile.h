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
	// Left coordinate of the tile in image pixels
	int x;
	// Top coordinate of the tile in image pixels
	int y;

	// Tile width in pixels, clipped at the image's right edge
	size_t width;
	// Tile height in pixels, clipped at the image's bottom edge
	size_t height;
};

/**
 * Generates a collection of tiles covering the complete image.
 * Edge tiles are automatically adjusted when image dimensions
 * are not multiples of the requested tile dimensions.
 *
 * @param imageWidth Image width in pixels.
 * @param imageHeight Image height in pixels.
 * @param tileSizeX Tile width.
 * @param tileSizeY Tile height.
 * @return Collection of generated image tiles.

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
 * Uses the same tile dimension for both horizontal
 * and vertical directions (Square tiles).
 *
 * @param imageWidth Image width in pixels.
 * @param imageHeight Image height in pixels.
 * @param tileSize Width and height of each tile.
 * @return Collection of generated image tiles.

 */
static std::vector<Tile> GenerateTiles(size_t imageWidth, size_t imageHeight,
	size_t tileSize)
{
	return GenerateTiles(imageWidth, imageHeight, tileSize, tileSize);
}

#endif // RAYTRACER_TILE_H