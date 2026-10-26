#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Maths/Vec3.h"

class Camera
{
public:
	Camera(Vec3 inCenter = Vec3(0, 0, 0), float inFocalLength = 1.0f);

	Vec3 GetCenter() const { return center; }
	float GetFocalLength() const { return focalLength; }

private:
	Vec3 center;
	float focalLength;
};

#endif