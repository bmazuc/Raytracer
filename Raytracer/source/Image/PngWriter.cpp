#include "Image/PngWriter.h"
#include "Image/ImageBuffer.h"
#include "Utils/NumericUtils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

bool PngWriter::Write(const std::string& filename, const ImageBuffer& frameBuffer) const
{
	if (!frameBuffer.IsValid())
	{
		return false;
	}

	std::vector<unsigned char> imageData = frameBuffer.GetImageData();

	const int width = NumericUtils::ToInt(frameBuffer.GetWidth());
	const int height = NumericUtils::ToInt(frameBuffer.GetHeight());
	const int stride = NumericUtils::ToInt(frameBuffer.GetWidth() * 3);

	return stbi_write_png(
		filename.c_str(),
		width,
		height,
		3,
		imageData.data(),
		stride
	) != 0;
}