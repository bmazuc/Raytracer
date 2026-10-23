#ifndef __IMAGE_H_INCLUDED__
#define __IMAGE_H_INCLUDED__

class Image
{
public:
	Image(int inWidth, int inHeight);

	void Render();

private:
	int width = 256;
	int height = 256;
};

#endif // __IMAGE_H_INCLUDED__