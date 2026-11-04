#include "Image/PngWriter.h"
#include "Image/ImageBuffer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

bool PngWriter::Write(const std::string& filename, const ImageBuffer& frameBuffer) const
{
	if (!frameBuffer.IsValid())
	{
		return false;
	}

	std::vector<unsigned char> imageData = frameBuffer.GetImageData();

	return stbi_write_png(
		filename.c_str(),
		frameBuffer.GetWidth(),
		frameBuffer.GetHeight(),
		3,
		imageData.data(),
		frameBuffer.GetWidth() * 3
	) != 0;
}