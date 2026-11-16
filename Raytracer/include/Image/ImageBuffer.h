#ifndef RAYTRACER_IMAGE_BUFFER_H
#define RAYTRACER_IMAGE_BUFFER_H

#include "Color.h"

#include <vector>
#include <stdexcept>
#include <cstdint>

/**
 * Stores image into a buffer containing RGB pixel data.
 */
class ImageBuffer
{
public:
	ImageBuffer(size_t inWidth = 1, size_t inHeight = 1);

	/**
	 * Updates the corresponding pixel in the internal image buffer.
	 *
	 * @param x Horizontal pixel coordinate.
	 * @param y Vertical pixel coordinate.
	 * @param color Color to assign to the pixel.
	 */
	void SetPixel(int x, int y, const Color& color);
	/**
	 * Retrieves the color stored at the specified pixel coordinates.
	 *
	 * @param x Horizontal pixel coordinate.
	 * @param y Vertical pixel coordinate.
	 * @return Constant reference to the requested pixel color.
	 */
	const Color& GetPixel(int x, int y) const;

	size_t GetWidth() const { return width; }
	size_t GetHeight() const { return height; }

	/**
	 * Checks whether the image buffer contains valid image data.
	 *
	 * @return True if the buffer dimensions and pixel storage are valid.
	 */
	bool IsValid() const;

	/**
	 * Converts floating-point color components into byte values
	 * suitable for image encoding and display.
	 *
	 * @return Pixel data in the expected RGB byte representation.
	 */
	std::vector<unsigned char> GetImageData() const;

private:
	size_t width;
	size_t height;
	// Pixel colors stored in row-major order
	std::vector<Color> pixels;
};

#endif // RAYTRACER_IMAGE_BUFFER_H