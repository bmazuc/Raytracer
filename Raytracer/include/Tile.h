#ifndef RAYTRACER_TILE_H
#define RAYTRACER_TILE_H

#include <vector>

// Tile represent a rectangle region of the image.
struct Tile
{
public:
	int x;
	int y;

	int width;
	int height;
};

// Generate rectangle tiles
static std::vector<Tile> GenerateTiles(int imageWidth, int imageHeight,
	int tileSizeX, int tileSizeY)
{
	std::vector<Tile> tiles;

	for (int y = 0; y < imageHeight; y += tileSizeY)
	{
		for (int x = 0; x < imageWidth; x += tileSizeX)
		{
			tiles.push_back({
					x,
					y,
					std::min(tileSizeX, imageWidth - x),
					std::min(tileSizeY, imageHeight - y)
				});
		}
	}

	return tiles;
}

// Generate square tiles
static std::vector<Tile> GenerateTiles(int imageWidth, int imageHeight,
	int tileSize)
{
	return GenerateTiles(imageWidth, imageHeight, tileSize, tileSize);
}

#endif // RAYTRACER_TILE_H