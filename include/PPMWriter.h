#ifndef __PPM_WRITER_H_INCLUDED__
#define __PPM_WRITER_H_INCLUDED__

#include <ostream>

struct Color;
class FrameBuffer;

class PPMWriter
{
public:
	PPMWriter(std::ostream& inOutput);

	void Write(const FrameBuffer& frameBuffer) const;

private:
	void WriteHeader(int width, int height) const;
	void WritePixel(const Color& color) const;

	std::ostream& output;
};

#endif // __PPM_WRITER_H_INCLUDED__