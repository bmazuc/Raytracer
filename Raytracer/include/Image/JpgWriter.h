#ifndef RAYTRACER_JPG_WRITER_H
#define RAYTRACER_JPG_WRITER_H

#include "Image/ImageWriter.h"

class JpgWriter : public ImageWriter
{
public:
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // RAYTRACER_JPG_WRITER_H