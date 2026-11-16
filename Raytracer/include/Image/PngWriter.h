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
     * Encodes and exports an image buffer as a PNG file.
	 *
	 * Uses the PNG encoding library to write the image data
	 * to the specified destination.
	 *
	 * @param filename Destination PNG file path.
	 * @param frameBuffer Image buffer to export.
	 * @return True if the image was successfully encoded and written.
	 */
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // RAYTRACER_PNG_WRITER_H