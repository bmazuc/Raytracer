#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Maths/Vec3.h"
#include <vector>

class Viewport;
struct Ray;

class Camera
{
public:
	Camera(int inImageWidth, int inImageHeight, Vec3 inCenter = Vec3(0,0,0), float inFocalLength = 1.0f, int inSamplesPerPixel = 10);
	Camera(int inImageWidth, float aspectRatio, Vec3 inCenter = Vec3(0, 0, 0), float inFocalLength = 1.0f, int inSamplesPerPixel = 10);

	Vec3 GetCenter() const { return center; }
	float GetFocalLength() const { return focalLength; }
	int GetImageWidth() const { return imageWidth; }
	int GetImageHeight() const { return imageHeight; }

	float GetPixelSamplesScale() const { return pixelSamplesScale; }

	void SetCenter(Vec3 inCenter) { center = inCenter; }
	void SetFocalLength(float inFocalLength) { focalLength = inFocalLength; }

	std::vector<Ray> GetRaySamplesForPixel(int x, int y) const;
	Ray ViewportPointToRay(int x, int y) const;

private:
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	Vec3 SampleSquare() const;

	Vec3 center;
	float focalLength;
	int samplesPerPixel; // Count of random samples for each pixel
	float pixelSamplesScale;  // Color scale factor for a sum of pixel samples


	int imageWidth;
	int imageHeight;

	Viewport* viewport = nullptr;
};

#endif