#ifndef RAYTRACER_IMAGE_WRITER_H
#define RAYTRACER_IMAGE_WRITER_H

#include <string>
#include <vector>

class ImageBuffer;

/**
 * Abstraction for image file writers.
 * 
 * Provides a common contract for exporting image buffers
 * to different file formats.
 */
class ImageWriter
{
public:
	virtual ~ImageWriter() = default;

	virtual bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const = 0;
};

#endif // RAYTRACER_IMAGE_WRITER_H