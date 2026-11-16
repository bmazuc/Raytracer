#ifndef RAYTRACER_JPG_WRITER_H
#define RAYTRACER_JPG_WRITER_H

#include "Image/ImageWriter.h"

/**
 * Exports image using the JPG file format.
 */
class JpgWriter : public ImageWriter
{
public:
	/**
	 * @return True on success, false if image buffer is invalid
	 * or writing failed.
	 */
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // RAYTRACER_JPG_WRITER_H