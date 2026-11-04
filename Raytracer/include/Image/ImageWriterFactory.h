#ifndef __IMAGE_WRITER_H_INCLUDED__
#define __IMAGE_WRITER_H_INCLUDED__

#include <memory>
#include <string>

class ImageWriter;

namespace ImageWriterFactory
{
	std::unique_ptr<ImageWriter> CreateImageWriter(const std::string& extension);
}

#endif // __IMAGE_WRITER_H_INCLUDED__