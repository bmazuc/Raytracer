#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Maths/Vec3.h"
#include "Viewport.h"
#include <vector>

struct Ray;

struct CameraConfiguration
{
public:
	size_t imageWidth = 255;
	float aspectRatio = 16.0f/9.0f;

	float fov = 90.0f; // Vertical view angle (field of view)

	Vec3 position = Vec3(0.0f, 0.0f, 0.0f); // Point camera is looking from
	Vec3 lookAt = Vec3(0.0f, 0.0f, -1.0f); // Point camera is looking at
	Vec3 vUp = Vec3(0.0f, 1.0f, 0.0f); // Camera-relative "vUp" direction

	unsigned int samplesPerPixel = 10; // Count of random samples for each pixel
	unsigned int maxDepth = 10; // Maximum number of ray bounces into scene

	float defocusAngle = 0.0f; // Variation angle of rays through each pixel
	float focusDistance = 10.0f; // Distance from camera lookfrom point to plane of perfect focus

	void Sanitize();
};

class Camera
{
public:
	Camera(const CameraConfiguration& config);

	float GetFov() const { return configuration.fov; }

	CameraConfiguration GetConfiguration() const;

	size_t GetImageWidth() const { return configuration.imageWidth; }
	size_t GetImageHeight() const { return imageHeight; }

	Vec3 GetPosition() const { return configuration.position; }
	Vec3 GetLookAt() const { return configuration.lookAt; }
	Vec3 GetVUp() const { return configuration.vUp; }

	Vec3 GetBackward() const { return backward; }
	Vec3 GetRight() const { return right; }
	Vec3 GetUp() const { return up; }

	float GetFocusDistance() const { return configuration.focusDistance; }
	float GetPixelSamplesScale() const { return pixelSamplesScale; }
	int GetMaxDepth() const { return configuration.maxDepth; }

	void SetConfiguration(const CameraConfiguration& config);

	void SetImageWidth(int inImageWidth);
	void SetAspectRatio(float inAspectRatio);
	
	void SetFov(float inFov);
	void SetSamplesPerPixel(int inSamplesPerPixel);

	void SetPosition(Vec3 inPosition);
	void SetLookAt(Vec3 inLookAt);
	void SetVUp(Vec3 inVUp);

	void SetMaxDepth(int inMaxDepth) { configuration.maxDepth = inMaxDepth; }

	void SetDefocusAngle(float inDefocusAngle);
	void SetFocusDistance(float inFocusDistance);

	std::vector<Ray> GetRaySamplesForPixel(int x, int y) const;
	Ray ViewportPointToRay(int x, int y) const;

private:
	void ComputeImageHeight();
	void ComputeCameraBasis();
	void ComputeDefocusDisk();

	// Returns a random point in the camera defocus disk.
	Vec3 DefocusDiskSample() const;
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	Vec3 SampleSquare() const;

	CameraConfiguration configuration;

	size_t imageHeight;

	Vec3 right;
	Vec3 up;
	Vec3 backward;

	float pixelSamplesScale;  // Color scale factor for a sum of pixel samples

	Vec3 defocusDiskU; // Defocus disk horizontal radius
	Vec3 defocusDiskV; // Defocus disk vertical radius

	Viewport viewport;
};

#endif // RAYTRACER_CAMERA_H