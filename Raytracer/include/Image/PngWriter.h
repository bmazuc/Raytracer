#ifndef RAYTRACER_PNG_WRITER_H
#define RAYTRACER_PNG_WRITER_H

#include "Image/ImageWriter.h"

class PngWriter : public ImageWriter
{
public:
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // RAYTRACER_PNG_WRITER_H