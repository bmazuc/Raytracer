#include "Camera.h"
#include "Viewport.h"
#include "Ray.h"
#include "Maths/MathsUtils.h"
#include "Utils/Log.h"

void CameraConfiguration::Sanitize()
{
	if (!std::isfinite(imageWidth) || imageWidth == 0)
	{
		Log::Warning("Camera : Image width == " + std::to_string(imageWidth) + " is invalid. Using 1 instead.");
		imageWidth = 1;
	}

	if (!std::isfinite(aspectRatio) || aspectRatio <= 0)
	{
		Log::Warning("Camera : Aspect ratio == " + std::to_string(aspectRatio) + " is invalid. Using 16:9 instead.");
		aspectRatio = 16.0f / 9.0f;
	}

	if (!std::isfinite(samplesPerPixel) || samplesPerPixel == 0)
	{
		Log::Warning("Camera : Samples per pixel == " + std::to_string(samplesPerPixel) + " is invalid. Using 1 instead.");
		samplesPerPixel = 1;
	}
}

Camera::Camera(const CameraConfiguration& config)
{
	SetCameraConfiguration(config);
}

CameraConfiguration Camera::GetConfiguration() const
{
	return configuration;
}

void Camera::SetCameraConfiguration(const CameraConfiguration& config)
{
	configuration = config;
	configuration.Sanitize();

	ComputeImageHeight();

	pixelSamplesScale = 1.0f / configuration.samplesPerPixel;

	ComputeCameraBasis();

	ComputeDefocusDisk();

	viewport.ComputeViewportData(this);
}

std::vector<Ray> Camera::GetRaySamplesForPixel(int x, int y) const
{
	std::vector<Ray> samples;

	for (unsigned int sample = 0; sample < configuration.samplesPerPixel; ++sample)
	{
		Vec3 offset = SampleSquare();
		Vec3 pixelSample = viewport.GetPixelSample(x, y, offset);

		Vec3 rayOrigin = (configuration.defocusAngle <= 0) ? configuration.position : DefocusDiskSample();
		Vec3 rayDirection = pixelSample - rayOrigin;

		samples.push_back(Ray(rayOrigin, rayDirection));
	}

	return samples;
}

Ray Camera::ViewportPointToRay(int x, int y) const
{
	Vec3 rayOrigin = (configuration.defocusAngle <= 0) ? configuration.position : DefocusDiskSample();
	Vec3 rayDirection = viewport.GetPixelCenter(x, y) - rayOrigin;

	return Ray(rayOrigin, rayDirection);
}

void Camera::ComputeImageHeight()
{
	int computedImageHeight = static_cast<int>(configuration.imageWidth / configuration.aspectRatio);
	imageHeight = std::max(1, computedImageHeight);
}

void Camera::ComputeCameraBasis()
{
	backward = (configuration.position - configuration.lookAt).GetNormal();
	right = Vec3::Cross(configuration.vUp, backward).GetNormal();
	up = Vec3::Cross(backward, right);
}

void Camera::ComputeDefocusDisk()
{
	float defocusRadius = configuration.focusDistance * std::tan(MathsUtils::DegreesToRadians(configuration.defocusAngle / 2.0f));

	defocusDiskU = right * defocusRadius;
	defocusDiskV = up * defocusRadius;
}

Vec3 Camera::DefocusDiskSample() const
{
	Vec3 p = Vec3::RandomInUnitDisk();
	return configuration.position + (p.x * defocusDiskU) + (p.y * defocusDiskV);
}

Vec3 Camera::SampleSquare() const
{
	return Vec3(MathsUtils::Random() - 0.5f, MathsUtils::Random() - 0.5f, 0.0f);
}

void Camera::SetImageWidth(int inImageWidth)
{
	configuration.imageWidth = inImageWidth;
	ComputeImageHeight();
	viewport.ComputeViewportData(this);
}

void Camera::SetAspectRatio(float inAspectRatio)
{
	configuration.aspectRatio = inAspectRatio;
	ComputeImageHeight();
	viewport.ComputeViewportData(this);
}

void Camera::SetFov(float inFov)
{
	configuration.fov = inFov;
	viewport.ComputeViewportData(this);
}

void Camera::SetSamplesPerPixel(int inSamplesPerPixel)
{
	configuration.samplesPerPixel = std::max(inSamplesPerPixel, 1);
	pixelSamplesScale = 1.0f / configuration.samplesPerPixel;
}

void Camera::SetPosition(Vec3 inPosition)
{
	configuration.position = inPosition;
	ComputeCameraBasis();
	viewport.ComputeViewportData(this);
}

void Camera::SetLookAt(Vec3 inLookAt)
{
	configuration.lookAt = inLookAt;
	ComputeCameraBasis();
	viewport.ComputeViewportData(this);
}

void Camera::SetVUp(Vec3 inVUp)
{
	configuration.vUp = inVUp;
	ComputeCameraBasis();
	viewport.ComputeViewportData(this);
}

void Camera::SetDefocusAngle(float inDefocusAngle)
{
	configuration.defocusAngle = inDefocusAngle;
	ComputeDefocusDisk();
	viewport.ComputeViewportData(this);
}

void Camera::SetFocusDistance(float inFocusDistance)
{
	configuration.focusDistance = inFocusDistance;
	ComputeDefocusDisk();
	viewport.ComputeViewportData(this);
}