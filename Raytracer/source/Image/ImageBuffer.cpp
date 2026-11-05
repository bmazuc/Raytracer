#include "Image/ImageBuffer.h"
#include "Maths/Interval.h"
#include "Utils/Log.h"

ImageBuffer::ImageBuffer(size_t inWidth, size_t inHeight)
	: width(inWidth), height(inHeight)
{
	if (!std::isfinite(width) || width == 0)
	{
		Log::Warning("ImageBuffer : Image created with width == " + std::to_string(width) + ". Using 1 instead.");
		width = 1;
	}

	if (!std::isfinite(height) || height == 0)
	{
		Log::Warning("ImageBuffer : Image created with height == " + std::to_string(height) + ". Using 1 instead.");
		height = 1;
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

void ImageBuffer::SetPixel(int x, int y, const Color& color)
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

const Color& ImageBuffer::GetPixel(int x, int y) const
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

bool ImageBuffer::IsValid() const
{
	return (width > 0 && height > 0 && pixels.size() == width * height);
}

std::vector<unsigned char> ImageBuffer::GetImageData() const
{
	std::vector<unsigned char> imageData(width * height * 3);

	const Interval intensity(0.000f, 0.999f);

	for (size_t idx = 0; idx < width * height; ++idx)
	{
		Color gammaColor = Color::LinearToGamma(pixels[idx]);

		// Translate the [0,1] component values to the byte range [0,255].
		const Interval intensity(0.000f, 0.999f);
		int rbyte = int(255.999f * intensity.Clamp(gammaColor.r));
		int gbyte = int(255.999f * intensity.Clamp(gammaColor.g));
		int bbyte = int(255.999f * intensity.Clamp(gammaColor.b));

		const size_t dataIdx = idx * 3;

		imageData[dataIdx] = static_cast<unsigned char>(rbyte);
		imageData[dataIdx + 1] = static_cast<unsigned char>(gbyte);
		imageData[dataIdx + 2] = static_cast<unsigned char>(bbyte);
	}

	return imageData;
}