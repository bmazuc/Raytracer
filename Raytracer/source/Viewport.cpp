#include "Viewport.h"
#include "Camera.h"
#include "Maths/Maths.h"

void Viewport::ComputeViewportData(const Camera* camera)
{
	if (!camera)
	{
		return;
	}

	size_t imageWidth = camera->GetImageWidth();
	size_t imageHeight = camera->GetImageHeight();

	float theta = maths::DegreesToRadians(camera->GetFov());
	float h = std::tan(theta / 2.0f);

	float height = 2.0f * h * camera->GetFocusDistance();
	float width = height * (static_cast<float>(imageWidth) / imageHeight);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	Vec3 viewportU = width * camera->GetRight(); // Vector across viewport horizontal edge
	Vec3 viewportV = height * -camera->GetUp(); // Vector down viewport vertical edge

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	pixelDeltaU = viewportU / static_cast<float>(imageWidth);
	pixelDeltaV = viewportV / static_cast<float>(imageHeight);

	// Calculate the location of the upper left pixel.
	Vec3 viewport_upper_left = camera->GetPosition()
		- camera->GetFocusDistance() * camera->GetBackward()
		- viewportU / 2.0f - viewportV / 2.0f;
	pixel00 = viewport_upper_left + 0.5f * (pixelDeltaU + pixelDeltaV);
}

Vec3 Viewport::GetPixelSample(int x, int y, const Vec3& offset) const
{
	return pixel00 + ((x + offset.x) * pixelDeltaU) + ((y + offset.y) * pixelDeltaV);
}

Vec3 Viewport::GetPixelCenter(int x, int y) const
{
	return pixel00 
		+ (static_cast<float>(x) * pixelDeltaU) 
		+ (static_cast<float>(y) * pixelDeltaV);
}