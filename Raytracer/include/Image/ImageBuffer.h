#ifndef __FRAME_BUFFER_H_INCLUDED__
#define __FRAME_BUFFER_H_INCLUDED__

#include "Color.h"

#include <vector>

class ImageBuffer
{
public:
	ImageBuffer(int inWidth, int inHeight)
		: width(inWidth), height(inHeight), pixels(width* height)
	{
	}

	void SetPixel(int x, int y, const Color& color)
	{
		pixels[y * width + x] = color;
	}

	const Color& GetPixel(int x, int y) const
	{
		return pixels[y * width + x];
	}

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	bool IsValid() const;

	std::vector<unsigned char> GetImageData() const;

private:
	int width;
	int height;
	std::vector<Color> pixels;
};

#endif // __FRAME_BUFFER_H_INCLUDED__