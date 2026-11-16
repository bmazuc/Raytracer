#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

/**
 * Represents an RGB color using floating-point components.
 */
struct Color
{
public:
	float r;
	float g;
	float b;

	Color();
	Color(float inR, float inG, float inB);

	Color operator+(const Color& rhs) const;
	Color operator-(const Color& rhs) const;
	Color operator*(const Color& rhs) const;
	Color operator*(float f) const;
	Color operator/(const Color& rhs) const;
	Color operator/(float f) const;

	Color& operator+=(const Color& rhs);
	Color& operator-=(const Color& rhs);
	Color& operator*=(const Color& rhs);
	Color& operator*=(float f);
	Color& operator/=(const Color& rhs);
	Color& operator/=(float f);

	//shorthands
	static const Color black;
	static const Color blue;
	static const Color cyan;
	static const Color gray;
	static const Color green;
	static const Color grey;
	static const Color magenta;
	static const Color red;
	static const Color white;
	static const Color yellow;

	/**
	 * Linearly interpolates between two colors.
	 *
	 * @param colorA Starting color.
	 * @param colorB Destination color.
	 * @param t Interpolation factor.
	 * @return Interpolated color.
	 */
	static Color Lerp(const Color& colorA, const Color& colorB, float t);
	
	/**
	 * Generates a random RGB color with components in [0, 1).
	 *
	 * @return Random color.
	 */
	static Color Random();
	/**
	 * Generates a random RGB color with components
	 * in the specified range.
	 *
	 * @param min Minimum component value.
	 * @param max Maximum component value.
	 * @return Random color.
	 */
	static Color Random(float min, float max);

	/**
	 *  Converts a linear RGB color to gamma-corrected RGB.
	 *
	 * Applies the square-root approximation commonly used
	 * for gamma correction in ray tracing.
	 *
	 * @param color Linear RGB color.
	 * @return Gamma-corrected color.
	 */
	static Color LinearToGamma(const Color& color);
};

inline Color operator*(float f, const Color& rhs)
{
	return rhs * f;
}

inline Color operator/(float f, const Color& rhs)
{
	return rhs / f;
}

#endif // RAYTRACER_COLOR_H