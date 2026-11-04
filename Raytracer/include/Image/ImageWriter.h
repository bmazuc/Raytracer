#ifndef __IMAGE_WRITER_INCLUDED__
#define __IMAGE_WRITER_INCLUDED__

#include <string>
#include <vector>

class ImageBuffer;

class ImageWriter
{
public:
	virtual ~ImageWriter() = default;

	virtual bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const = 0;
};

#endif // __IMAGE_WRITER_INCLUDED__