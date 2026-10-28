#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Maths/Vec3.h"
#include <vector>

class Viewport;
struct Ray;

struct CameraConfiguration
{
public:
	Vec3 center = Vec3(0, 0, 0);

	int imageWidth;
	float aspectRatio;

	float focalLength = 1.0f;
	int samplesPerPixel = 10;
	int maxDepth = 10;
};

class Camera
{
public:
	Camera(const CameraConfiguration& config);

	Vec3 GetCenter() const { return center; }
	float GetFocalLength() const { return focalLength; }
	int GetImageWidth() const { return imageWidth; }
	int GetImageHeight() const { return imageHeight; }

	float GetPixelSamplesScale() const { return pixelSamplesScale; }
	int GetMaxDepth() const { return maxDepth; }

	void SetCenter(Vec3 inCenter) { center = inCenter; }
	void SetFocalLength(float inFocalLength) { focalLength = inFocalLength; }

	std::vector<Ray> GetRaySamplesForPixel(int x, int y) const;
	Ray ViewportPointToRay(int x, int y) const;

private:
	void ComputeImageHeight();

	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	Vec3 SampleSquare() const;

	Vec3 center;
	float focalLength;

	float aspectRatio;

	int samplesPerPixel; // Count of random samples for each pixel
	float pixelSamplesScale;  // Color scale factor for a sum of pixel samples

	int maxDepth; // Maximum number of ray bounces into scene

	int imageWidth;
	int imageHeight;

	Viewport* viewport = nullptr;
};

#endif