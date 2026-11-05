#ifndef RAYTRACER_PPM_WRITER_H
#define RAYTRACER_PPM_WRITER_H

#include "Image/ImageWriter.h"

#include <ostream>

struct Color;
class ImageBuffer;

class PPMWriter : public ImageWriter
{
public:
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;

private:
	void WriteHeader(std::ofstream& output, int width, int height) const;
	void WritePixel(std::ofstream& output, const Color& color) const;
};

#endif // RAYTRACER_PPM_WRITER_H