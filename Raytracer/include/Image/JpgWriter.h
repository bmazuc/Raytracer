#ifndef __JPG_WRITER_H_INCLUDED__
#define __JPG_WRITER_H_INCLUDED__

#include "Image/ImageWriter.h"

class JpgWriter : public ImageWriter
{
public:
	bool Write(const std::string& filename, const ImageBuffer& frameBuffer) const override;
};

#endif // __JPG_WRITER_H_INCLUDED__