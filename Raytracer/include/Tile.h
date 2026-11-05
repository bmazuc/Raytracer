#ifndef RAYTRACER_TILE_H
#define RAYTRACER_TILE_H

#include <vector>

// Tile represent a rectangle region of the image.
struct Tile
{
public:
	int x;
	int y;

	size_t width;
	size_t height;
};

// Generate rectangle tiles
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

// Generate square tiles
static std::vector<Tile> GenerateTiles(size_t imageWidth, size_t imageHeight,
	size_t tileSize)
{
	return GenerateTiles(imageWidth, imageHeight, tileSize, tileSize);
}

#endif // RAYTRACER_TILE_H