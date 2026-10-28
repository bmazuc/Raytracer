#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Maths/Maths.h"

Camera::Camera(const CameraConfiguration& config)
{
	center = config.center;

	imageWidth = config.imageWidth;
	aspectRatio = config.aspectRatio;
	ComputeImageHeight();

	focalLength = config.focalLength;

	samplesPerPixel = config.samplesPerPixel;
	pixelSamplesScale = 1.0f / samplesPerPixel;

	maxDepth = config.maxDepth;

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

void Camera::ComputeImageHeight()
{
	int computedImageHeight = int(imageWidth / aspectRatio);
	if (computedImageHeight < 1)
	{
		computedImageHeight = 1;
	}

	imageHeight = computedImageHeight;
}

Vec3 Camera::SampleSquare() const
{
	return Vec3(maths::Random() - 0.5f, maths::Random() - 0.5f, 0.0f);
}