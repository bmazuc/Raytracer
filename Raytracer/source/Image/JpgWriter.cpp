#include "Image/JpgWriter.h"
#include "Image/ImageBuffer.h"
#include "Utils/NumericUtils.h"

#include <stb_image_write.h>

bool JpgWriter::Write(const std::string& filename, const ImageBuffer& frameBuffer) const
{
	if (!frameBuffer.IsValid())
	{
		return false;
	}

	std::vector<unsigned char> imageData = frameBuffer.GetImageData();

	const int width = NumericUtils::ToInt(frameBuffer.GetWidth());
	const int height = NumericUtils::ToInt(frameBuffer.GetHeight());
	const int stride = NumericUtils::ToInt(frameBuffer.GetWidth() * 3);

	return stbi_write_jpg(
		filename.c_str(),
		width,
		height,
		3,
		imageData.data(),
		stride
	) != 0;
}