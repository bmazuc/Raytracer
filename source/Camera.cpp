#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"

Camera::Camera(int inImageWidth, int inImageHeight, Vec3 inCenter, float inFocalLength)
	: center(inCenter), focalLength(inFocalLength), imageWidth(inImageWidth), imageHeight(inImageHeight)
{
	viewport = new Viewport(this, imageWidth, imageHeight);
}

Camera::Camera(int inImageWidth, float aspectRatio, Vec3 inCenter, float inFocalLength)
	: center(inCenter), focalLength(inFocalLength), imageWidth(inImageWidth)
{
	int computedImageHeight = int(inImageWidth / aspectRatio);
	if (computedImageHeight < 1)
	{
		computedImageHeight = 1;
	}

	imageHeight = computedImageHeight;

	viewport = new Viewport(this, imageWidth, imageHeight);
}

Ray Camera::ViewportPointToRay(int x, int y)
{
	Vec3 rayDirection = viewport->GetPixelCenter(x, y) - center;
	return Ray(center, rayDirection);
}