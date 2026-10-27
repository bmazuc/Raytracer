#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Maths/Maths.h"

Camera::Camera(int inImageWidth, int inImageHeight, Vec3 inCenter, float inFocalLength, int inSamplesPerPixel)
	: center(inCenter), focalLength(inFocalLength), imageWidth(inImageWidth), imageHeight(inImageHeight), samplesPerPixel(inSamplesPerPixel)
{
	pixelSamplesScale = 1.0f / samplesPerPixel;

	viewport = new Viewport(this, imageWidth, imageHeight);
}

Camera::Camera(int inImageWidth, float aspectRatio, Vec3 inCenter, float inFocalLength, int inSamplesPerPixel)
	: center(inCenter), focalLength(inFocalLength), imageWidth(inImageWidth), samplesPerPixel(inSamplesPerPixel)
{
	int computedImageHeight = int(inImageWidth / aspectRatio);
	if (computedImageHeight < 1)
	{
		computedImageHeight = 1;
	}

	imageHeight = computedImageHeight;

	pixelSamplesScale = 1.0f / samplesPerPixel;

	viewport = new Viewport(this, imageWidth, imageHeight);
}

std::vector<Ray> Camera::GetRaySamplesForPixel(int x, int y) const
{
	std::vector<Ray> samples;

	for (int sample = 0; sample < samplesPerPixel; ++sample)
	{
		Vec3 offset = SampleSquare();
		Vec3 pixelSample = viewport->GetPixelSample(x, y, offset);

		Vec3 rayOrigin = center;
		Vec3 rayDirection = pixelSample - rayOrigin;

		samples.push_back(Ray(rayOrigin, rayDirection));
	}

	return samples;
}

Ray Camera::ViewportPointToRay(int x, int y) const
{
	Vec3 rayDirection = viewport->GetPixelCenter(x, y) - center;
	return Ray(center, rayDirection);
}

Vec3 Camera::SampleSquare() const
{
	return Vec3(maths::Random() - 0.5f, maths::Random() - 0.5f, 0.0f);
}