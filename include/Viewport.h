#ifndef __VIEWPORT_H_INCLUDED__
#define __VIEWPORT_H_INCLUDED__

#include "Vec3.h"

class Camera;

class Viewport
{
public:
	Viewport(const Camera* camera, int imageWidth, int imageHeight);

	Vec3 GetPixelCenter(int x, int y);

private:
	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;
	Vec3 pixel00;
};

#endif // __VIEWPORT_H_INCLUDED__