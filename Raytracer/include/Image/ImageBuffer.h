#ifndef RAYTRACER_IMAGE_BUFFER_H
#define RAYTRACER_IMAGE_BUFFER_H

#include "Color.h"

#include <vector>
#include <stdexcept>
#include <cstdint>

constexpr size_t maxSize = SIZE_MAX;

class ImageBuffer
{
public:
	ImageBuffer(size_t inWidth, size_t inHeight)
		: width(inWidth), height(inHeight)
	{
		if (width == 0 || height == 0)
		{
			throw std::invalid_argument("Image dimensions must be greater than zero");
		}

		if (height > SIZE_MAX / width)
		{
			throw std::overflow_error("Image dimensions are too large");
		}

		const size_t pixelCount = width * height;

		if (pixelCount > SIZE_MAX / 3)
		{
			throw std::overflow_error("Image data size overflow");
		}

		pixels.resize(width * height);
	}

	void SetPixel(int x, int y, const Color& color)
	{
		if (x < 0 || y < 0 ||
			x >= static_cast<int>(width) ||
			y >= static_cast<int>(height))
		{
			return;
		}

		const size_t idx = static_cast<size_t>(y) * width + static_cast<size_t>(x);
		pixels[idx] = color;
	}

	const Color& GetPixel(int x, int y) const
	{
		if (x < 0 || y < 0 ||
			x >= static_cast<int>(width) ||
			y >= static_cast<int>(height))
		{
			return Color::black;
		}

		const size_t idx = static_cast<size_t>(y) * width + static_cast<size_t>(x);
		return pixels[idx];
	}

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