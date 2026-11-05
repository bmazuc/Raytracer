#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

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

	static Color Lerp(const Color& colorA, const Color& colorB, float t);
	
	static Color Random();
	static Color Random(float min, float max);

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