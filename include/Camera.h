#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Maths/Vec3.h"
#include <vector>

class Viewport;
struct Ray;

struct CameraConfiguration
{
public:
	int imageWidth;
	float aspectRatio;

	float fov = 90.0f; // Vertical view angle (field of view)

	Vec3 position = Vec3(0.0f, 0.0f, 0.0f); // Point camera is looking from
	Vec3 lookAt = Vec3(0.0f, 0.0f, -1.0f); // Point camera is looking at
	Vec3 up = Vec3(0.0f, 1.0f, 0.0f); // Camera-relative "up" direction

	int samplesPerPixel = 10;
	int maxDepth = 10;
};

class Camera
{
public:
	Camera(const CameraConfiguration& config);

	float GetFocalLength() const { return focalLength; }
	float GetFov() const { return fov; }

	int GetImageWidth() const { return imageWidth; }
	int GetImageHeight() const { return imageHeight; }

	Vec3 GetPosition() const { return position; }
	Vec3 GetLookAt() const { return lookAt; }
	Vec3 GetUp() const { return up; }

	void SetImageWidth(int inImageWidth);
	void SetAspectRatio(float inAspectRatio);
	
	void SetFov(float inFov);
	void SetSamplesPerPixel(int inSamplesPerPixel);

	void SetPosition(Vec3 inPosition);
	void SetLookAt(Vec3 inLookAt);
	void SetUp(Vec3 inUp);

	void SetMaxDepth(int inMaxDepth) { maxDepth = inMaxDepth; }

	float GetPixelSamplesScale() const { return pixelSamplesScale; }
	int GetMaxDepth() const { return maxDepth; }

	std::vector<Ray> GetRaySamplesForPixel(int x, int y) const;
	Ray ViewportPointToRay(int x, int y) const;

private:
	void ComputeImageHeight();

	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	Vec3 SampleSquare() const;

	float focalLength;
	float fov;

	Vec3 position;
	Vec3 lookAt;
	Vec3 up;

	float aspectRatio;

	int samplesPerPixel; // Count of random samples for each pixel
	float pixelSamplesScale;  // Color scale factor for a sum of pixel samples

	int maxDepth; // Maximum number of ray bounces into scene

	int imageWidth;
	int imageHeight;

	Viewport* viewport = nullptr;
};

#endif