#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Maths/Vec3.h"

class Viewport;
struct Ray;

class Camera
{
public:
	Camera(int inImageWidth, int inImageHeight, Vec3 inCenter = Vec3(0,0,0), float inFocalLength = 1.0f);
	Camera(int inImageWidth, float aspectRatio, Vec3 inCenter = Vec3(0, 0, 0), float inFocalLength = 1.0f);

	Vec3 GetCenter() const { return center; }
	float GetFocalLength() const { return focalLength; }
	int GetImageWidth() const { return imageWidth; }
	int GetImageHeight() const { return imageHeight; }

	void SetCenter(Vec3 inCenter) { center = inCenter; }
	void SetFocalLength(float inFocalLength) { focalLength = inFocalLength; }

	Ray ViewportPointToRay(int x, int y);

private:
	Vec3 center;
	float focalLength;

	int imageWidth;
	int imageHeight;

	Viewport* viewport = nullptr;
};

#endif