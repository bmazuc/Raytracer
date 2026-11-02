#ifndef __VIEWPORT_H_INCLUDED__
#define __VIEWPORT_H_INCLUDED__

#include "Maths/Vec3.h"

class Camera;

class Viewport
{
public:
	void ComputeViewportData(const Camera* camera);

	Vec3 GetPixelSample(int x, int y, const Vec3& offset) const;
	Vec3 GetPixelCenter(int x, int y) const;

private:
	Vec3 pixelDeltaU; // Offset to pixel to the right
	Vec3 pixelDeltaV; // Offset to pixel below
	Vec3 pixel00; // Location of pixel 0, 0
};

#endif // __VIEWPORT_H_INCLUDED__