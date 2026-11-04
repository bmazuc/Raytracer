#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Maths/Maths.h"

Camera::Camera(const CameraConfiguration& config)
{
	imageWidth = config.imageWidth;
	aspectRatio = config.aspectRatio;
	ComputeImageHeight();

	fov = config.fov;

	samplesPerPixel = config.samplesPerPixel;
	pixelSamplesScale = 1.0f / samplesPerPixel;

	maxDepth = config.maxDepth;

	defocusAngle = config.defocusAngle;
	focusDistance = config.focusDistance;

	position = config.position;
	lookAt = config.lookAt;
	vUp = config.vUp;
	ComputeCameraBasis();
	
	ComputeDefocusDisk();

	viewport.ComputeViewportData(this);
}

std::vector<Ray> Camera::GetRaySamplesForPixel(int x, int y) const
{
	std::vector<Ray> samples;

	for (int sample = 0; sample < samplesPerPixel; ++sample)
	{
		Vec3 offset = SampleSquare();
		Vec3 pixelSample = viewport.GetPixelSample(x, y, offset);

		Vec3 rayOrigin = (defocusAngle <= 0) ? position : DefocusDiskSample();
		Vec3 rayDirection = pixelSample - rayOrigin;

		samples.push_back(Ray(rayOrigin, rayDirection));
	}

	return samples;
}

Ray Camera::ViewportPointToRay(int x, int y) const
{
	Vec3 rayOrigin = (defocusAngle <= 0) ? position : DefocusDiskSample();
	Vec3 rayDirection = viewport.GetPixelCenter(x, y) - rayOrigin;

	return Ray(rayOrigin, rayDirection);
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

void Camera::ComputeCameraBasis()
{
	backward = (position - lookAt).GetNormal();
	right = Vec3::Cross(vUp, backward).GetNormal();
	up = Vec3::Cross(backward, right);
}

void Camera::ComputeDefocusDisk()
{
	float defocusRadius = focusDistance * std::tan(maths::DegreesToRadians(defocusAngle / 2.0f));

	defocusDiskU = right * defocusRadius;
	defocusDiskV = up * defocusRadius;
}

Vec3 Camera::DefocusDiskSample() const
{
	Vec3 p = Vec3::RandomInUnitDisk();
	return position + (p.x * defocusDiskU) + (p.y * defocusDiskV);
}

Vec3 Camera::SampleSquare() const
{
	return Vec3(maths::Random() - 0.5f, maths::Random() - 0.5f, 0.0f);
}

void Camera::SetImageWidth(int inImageWidth)
{
	imageWidth = inImageWidth;
	ComputeImageHeight();
	viewport.ComputeViewportData(this);
}

void Camera::SetAspectRatio(float inAspectRatio)
{
	aspectRatio = inAspectRatio;
	ComputeImageHeight();
	viewport.ComputeViewportData(this);
}

void Camera::SetFov(float inFov)
{
	fov = inFov;
	viewport.ComputeViewportData(this);
}

void Camera::SetSamplesPerPixel(int inSamplesPerPixel)
{
	samplesPerPixel = inSamplesPerPixel;
	pixelSamplesScale = 1.0f / samplesPerPixel;
}

void Camera::SetPosition(Vec3 inPosition)
{
	position = inPosition;
	ComputeCameraBasis();
	viewport.ComputeViewportData(this);
}

void Camera::SetLookAt(Vec3 inLookAt)
{
	lookAt = inLookAt;
	ComputeCameraBasis();
	viewport.ComputeViewportData(this);
}

void Camera::SetVUp(Vec3 inVUp)
{
	vUp = inVUp;
	ComputeCameraBasis();
	viewport.ComputeViewportData(this);
}

void Camera::SetDefocusAngle(float inDefocusAngle)
{
	defocusAngle = inDefocusAngle;
	ComputeDefocusDisk();
	viewport.ComputeViewportData(this);
}

void Camera::SetFocusDistance(float inFocusDistance)
{
	focusDistance = inFocusDistance;
	ComputeDefocusDisk();
	viewport.ComputeViewportData(this);
}