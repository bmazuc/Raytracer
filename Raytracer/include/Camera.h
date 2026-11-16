#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Maths/Vec3.h"
#include "Viewport.h"
#include <vector>

struct Ray;

/**
 * Stores the parameters used to configure a rendering camera.
 */
struct CameraConfiguration
{
public:
	// Image width in pixels
	size_t imageWidth = 255;
	// Image width-to-height ratio
	float aspectRatio = 16.0f/9.0f;

	// Vertical field of view in degrees
	float fov = 90.0f; 

	// Point camera is looking from
	Vec3 position = Vec3(0.0f, 0.0f, 0.0f); 
	// Point camera is looking at
	Vec3 lookAt = Vec3(0.0f, 0.0f, -1.0f);
	// Camera-relative "vUp" direction
	Vec3 vUp = Vec3(0.0f, 1.0f, 0.0f); 

	// Count of random samples for each pixel
	unsigned int samplesPerPixel = 10; 
	// Maximum number of ray bounces into scene
	unsigned int maxDepth = 10; 

	// Variation angle of rays through each pixel
	float defocusAngle = 0.0f; 
	// Distance from camera lookfrom point to plane of perfect focus
	float focusDistance = 10.0f; 

	/**
	 * Check and modify incorrect parameters.
	 */
	void Sanitize();
};

/**
 * Represent a camera responsible for generating rays
 * used to observe and sample a 3D scene.
 * Computes the camera coordinate system, viewport geometry,
 * pixel sampling positions and defocus effects.
 */
class Camera
{
public:
	/**
	 * Initializes the camera using the provided configuration.
	 *
	 * Computes the camera coordinate system, image dimensions,
	 * viewport geometry and depth-of-field parameters.
	 *
	 * @param config Initial camera configuration.
	 */
	Camera(const CameraConfiguration& config);

	float GetFov() const { return configuration.fov; }

	/**
	 * Provides a snapshot of the current camera parameters.
	 */
	CameraConfiguration GetConfiguration() const;

	/**
	 * Updates the camera configuration.
	 *
	 * Applies the provided parameters and recomputes the internal
	 * camera data required for ray generation.
	 *
	 * @param config The new camera configuration.
	*/
	void SetCameraConfiguration(const CameraConfiguration& config);

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

	/**
	 * Updates the camera image width.
	 *
	 * Recomputes the image dimensions and viewport data
	 * to reflect the new resolution.
	 *
	 * @param inImageWidth The new image width in pixels.
	 */
	void SetImageWidth(int inImageWidth);
	/**
	 * Updates the camera aspect ratio.
	 *
	 * Recomputes the image dimensions and viewport geometry.
	 *
	 * @param inAspectRatio The new image aspect ratio.
	 */
	void SetAspectRatio(float inAspectRatio);
	
	/**
	 * Updates the vertical field of view.
	 *
	 * Recomputes the viewport geometry using the new field of view.
	 *
	 * @param inFov The new vertical field of view in degrees.
	 */
	void SetFov(float inFov);
	/**
	 *  Updates the number of samples used for each pixel.
	 *
	 * Recomputes the scaling factor applied to accumulated
	 * pixel samples.
	 *
	 * @param inSamplesPerPixel The number of samples per pixel.
	 */
	void SetSamplesPerPixel(int inSamplesPerPixel);

	/**
	 *  Updates the camera position.
	 *
	 * Recomputes the camera coordinate system and viewport geometry.
	 *
	 * @param inPosition The new camera position in world space.
	 */
	void SetPosition(Vec3 inPosition);
	/**
	 * Updates the point the camera is looking at.
	 *
	 * Recomputes the camera orientation and viewport geometry.
	 *
	 * @param inLookAt The new target position in world space.
	 */
	void SetLookAt(Vec3 inLookAt);
	/**
	 * Updates the camera reference up direction.
	 *
	 * Recomputes the camera coordinate system and viewport geometry.
	 *
	 * @param inVUp The new reference up vector.
	 */
	void SetVUp(Vec3 inVUp);

	void SetMaxDepth(int inMaxDepth) { configuration.maxDepth = inMaxDepth; }

	/**
	 * Updates the camera defocus angle.
	 *
	 * Recomputes the defocus disk used to generate rays
	 * with depth-of-field effects.
	 *
	 * @param inDefocusAngle The new defocus angle in degrees.
	 */
	void SetDefocusAngle(float inDefocusAngle);
	/**
	 * Updates the camera focus distance.
	 *
	 * Recomputes the defocus disk using the new focus distance.
	 *
	 * @param inFocusDistance The new distance to the focus plane.
	 */
	void SetFocusDistance(float inFocusDistance);

	/**
	 *  Produces a collection of rays using randomized sampling
	 * to simulate anti-aliasing and depth-of-field effects
	 * for a given pixel.
	 *
	 * @param x Horizontal pixel coordinate.
	 * @param y Vertical pixel coordinate.
	 * @return The generated ray samples for the requested pixel.
	 */
	std::vector<Ray> GetRaySamplesForPixel(int x, int y) const;
	/**
	 * Converts the specified viewport pixel coordinates into
	 * a ray originating from the camera.
	 *
	 * @param x Horizontal pixel coordinate.
	 * @param y Vertical pixel coordinate.
	 * @return The generated camera ray.
	 */
	Ray ViewportPointToRay(int x, int y) const;

private:
	/**
	 * Computes the image height from the configured width and aspect ratio.
	 *
	 * Ensures that the camera image dimensions remain consistent
	 * with the configured aspect ratio.
	 */
	void ComputeImageHeight();
	/**
	 *  Calculates the orthonormal basis vectors used to orient
	 * the camera in world space.
	 */
	void ComputeCameraBasis();
	/**
	 * Determines the horizontal and vertical vectors defining
	 * the aperture used for depth-of-field sampling.
	 */
	void ComputeDefocusDisk();

	// Returns a random point in the camera defocus disk.
	Vec3 DefocusDiskSample() const;
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	Vec3 SampleSquare() const;

	// User-configurable camera parameters
	CameraConfiguration configuration;

	// Computed image height in pixels, derived from width and aspect ratio
	size_t imageHeight;

	// Camera-local horizontal axis in world space
	Vec3 right;
	// Camera-local vertical axis in world space
	Vec3 up;
	// Camera-local backward axis, opposite to the viewing direction
	Vec3 backward;

	// Color scale factor for a sum of pixel samples
	float pixelSamplesScale;  

	// Defocus disk horizontal radius
	Vec3 defocusDiskU; 
	// Defocus disk vertical radius
	Vec3 defocusDiskV;

	// Precomputed viewport geometry used to generate camera rays
	Viewport viewport;
};

#endif // RAYTRACER_CAMERA_H