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
	 * Encodes and exports an image buffer as a JPEG file.
	 *
	 * Uses the JPEG encoding library to write the image data
	 * to the specified destination.
	 *
	 * @param filename Destination JPEG file path.
	 * @param frameBuffer Image buffer to export.
	 * @return True if the image was successfully encoded and written.
	 */
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // RAYTRACER_JPG_WRITER_H