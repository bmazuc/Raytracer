#include "Image/ImageBuffer.h"
#include "Maths/Interval.h"

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