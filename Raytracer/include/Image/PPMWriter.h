#ifndef RAYTRACER_PPM_WRITER_H
#define RAYTRACER_PPM_WRITER_H

#include "Image/ImageWriter.h"

#include <ostream>

struct Color;
class ImageBuffer;

/**
 * Exports image using the PPM file format.
 */
class PPMWriter : public ImageWriter
{
public:
	/**
     * Exports an image buffer using the PPM file format.
	 *
	 * Writes the image header followed by the RGB pixel data.
	 *
	 * @param filename Destination PPM file path.
	 * @param frameBuffer Image buffer to export.
	 * @return True if the file was successfully written.
     */
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;

private:
	/**
	 * Writes the PPM image header.
	 *
	 * Outputs the format identifier and image dimensions.
	 *
	 * @param output Output file stream.
	 * @param width Image width in pixels.
	 * @param height Image height in pixels.
	 */
	void WriteHeader(std::ofstream& output, int width, int height) const;
	/**
	 *  Writes a pixel as RGB values to the output stream.
	 *
	 * @param output Output file stream.
	 * @param color Pixel color to write.
	 */
	void WritePixel(std::ofstream& output, const Color& color) const;
};

#endif // RAYTRACER_PPM_WRITER_H