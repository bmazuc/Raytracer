#include "Image/JpgWriter.h"
#include "Image/ImageBuffer.h"

#include "stb/stb_image_write.h"

bool JpgWriter::Write(const std::string& filename, const ImageBuffer& frameBuffer) const
{
	if (!frameBuffer.IsValid())
	{
		return false;
	}

	std::vector<unsigned char> imageData = frameBuffer.GetImageData();

	return stbi_write_jpg(
		filename.c_str(),
		frameBuffer.GetWidth(),
		frameBuffer.GetHeight(),
		3,
		imageData.data(),
		frameBuffer.GetWidth() * 3
	) != 0;
}