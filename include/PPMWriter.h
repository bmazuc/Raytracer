#ifndef __PPM_WRITER_H_INCLUDED__
#define __PPM_WRITER_H_INCLUDED__

#include <ostream>

struct Color;

class PPMWriter
{
public:
	PPMWriter(std::ostream& inOutput);

	void WriteHeader(int width, int height) const;
	void WritePixel(const Color& color) const;

private:
	std::ostream& output;
};

#endif // __PPM_WRITER_H_INCLUDED__