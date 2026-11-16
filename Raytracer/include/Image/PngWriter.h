#ifndef RAYTRACER_PNG_WRITER_H
#define RAYTRACER_PNG_WRITER_H

#include "Image/ImageWriter.h"

/**
 * Exports image using the PNG file format.
 */
class PngWriter : public ImageWriter
{
public:
	/**
     * @return True on success, false if image buffer is invalid
	 * or writing failed.
     */
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // RAYTRACER_PNG_WRITER_H