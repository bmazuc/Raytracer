#ifndef __PNG_WRITER_H_INCLUDED__
#define __PNG_WRITER_H_INCLUDED__

#include "Image/ImageWriter.h"

class PngWriter : public ImageWriter
{
public:
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // __PNG_WRITER_H_INCLUDED__