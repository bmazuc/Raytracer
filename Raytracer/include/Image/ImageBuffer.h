#ifndef RAYTRACER_IMAGE_BUFFER_H
#define RAYTRACER_IMAGE_BUFFER_H

#include "Color.h"

#include <vector>
#include <stdexcept>
#include <cstdint>

/**
 * Stores image into a buffer containing RGB pixel data.
 */
class ImageBuffer
{
public:
	ImageBuffer(size_t inWidth = 1, size_t inHeight = 1);

	void SetPixel(int x, int y, const Color& color);

	const Color& GetPixel(int x, int y) const;
	size_t GetWidth() const { return width; }
	size_t GetHeight() const { return height; }

	bool IsValid() const;

	std::vector<unsigned char> GetImageData() const;

private:
	size_t width;
	size_t height;
	std::vector<Color> pixels;
};

#endif // RAYTRACER_IMAGE_BUFFER_H