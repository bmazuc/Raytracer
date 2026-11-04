#ifndef __PPM_WRITER_H_INCLUDED__
#define __PPM_WRITER_H_INCLUDED__

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

#endif // __PPM_WRITER_H_INCLUDED__