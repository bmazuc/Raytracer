#ifndef RAYTRACER_VIEWPORT_H
#define RAYTRACER_VIEWPORT_H

#include "Maths/Vec3.h"

class Camera;

/**
 * Manages the geometric representation of the camera viewport.
 */
class Viewport
{
public:
	/**
	 * Computes the geometric data required to map pixels into 3D space.
	 *
	 * Uses the camera orientation, image dimensions and field of view
	 * to calculate the viewport origin and pixel displacement vectors.
	 *
	 * @param camera Camera providing the viewport configuration.
	 */
	void ComputeViewportData(const Camera* camera);

	/**
	 * Computes a randomized sampling position within a pixel.
	 *
	 * Applies the provided sampling offset to the specified pixel
	 * coordinates in the viewport.
	 *
	 * @param x Horizontal pixel coordinate.
	 * @param y Vertical pixel coordinate.
	 * @param offset Sampling offset within the pixel.
	 * @return The resulting sampling position in world space.
	 */
	Vec3 GetPixelSample(int x, int y, const Vec3& offset) const;
	/**
	 * Returns the center position of a pixel in world space.
	 *
	 * @param x Horizontal pixel coordinate.
	 * @param y Vertical pixel coordinate.
	 * @return The world-space position at the center of the pixel.
	 */
	Vec3 GetPixelCenter(int x, int y) const;

private:
	// Offset to pixel to the right
	Vec3 pixelDeltaU; 
	// Offset to pixel below
	Vec3 pixelDeltaV; 
	// Location of pixel 0, 0
	Vec3 pixel00; 
};

#endif // RAYTRACER_VIEWPORT_H