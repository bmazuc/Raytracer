#include "Viewport.h"
#include "Camera.h"

Viewport::Viewport(const Camera* camera, int imageWidth, int imageHeight)
{
	float height = 2.0f;
	float width = height * (float(imageWidth) / imageHeight);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	Vec3 u = Vec3(width, 0, 0);
	Vec3 v = Vec3(0, -height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	pixelDeltaU = u / imageWidth;
	pixelDeltaV = v / imageHeight;

	// Calculate the location of the upper left pixel.
	Vec3 viewport_upper_left = camera->GetCenter()
		- Vec3(0, 0, camera->GetFocalLength()) - u / 2 - v / 2;
	pixel00 = viewport_upper_left + 0.5f * (pixelDeltaU + pixelDeltaV);
}

Vec3 Viewport::GetPixelCenter(int x, int y)
{
	return pixel00 + (x * pixelDeltaU) + (y * pixelDeltaV );
}