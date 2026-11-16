#ifndef RAYTRACER_VIEWPORT_H
#define RAYTRACER_VIEWPORT_H

#include "Maths/Vec3.h"

class Camera;

/**
 * Manages the geometric representation of the camera viewport.
 */
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

#endif // RAYTRACER_VIEWPORT_H