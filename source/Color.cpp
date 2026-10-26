#include "Color.h"

const Color Color::black = Color(0.f, 0.f, 0.f);
const Color Color::blue = Color(0.f, 0.f, 1.f);
const Color Color::cyan = Color(0.f, 1.f, 1.f);
const Color Color::gray = Color(0.5f, 0.5f, 0.5f);
const Color Color::green = Color(0.f, 1.f, 0.f);
const Color Color::grey = Color(0.5f, 0.5f, 0.5f);
const Color Color::magenta = Color(1.f, 0.f, 1.f);
const Color Color::red = Color(1.f, 0.f, 0.f);
const Color Color::white = Color(1.f, 1.f, 1.f);
const Color Color::yellow = Color(1.f, 0.92f, 0.016f);

Color::Color()
	: r(0), g(0), b(0)
{
}

Color::Color(float inR, float inG, float inB)
	: r(inR), g(inG), b(inB)
{
}

Color Color::operator+(const Color& rhs) const
{
	return Color(r + rhs.r, g + rhs.g, b + rhs.b);
}

Color Color::operator-(const Color& rhs) const
{
	return Color(r - rhs.r, g - rhs.g, b - rhs.b);
}

Color Color::operator*(const Color& rhs) const
{
	return Color(r * rhs.r, g * rhs.g, b * rhs.b);
}

Color Color::operator*(float f) const
{
	return Color(r * f, g * f, b * f);
}

Color Color::operator/(const Color& rhs)
{
	return Color(r + rhs.r, g + rhs.g, b + rhs.b);
}

Color Color::operator/(float f) const
{
	return Color(r / f, g / f, b / f);
}

Color& Color::operator+=(const Color& rhs)
{
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
	return *this;
}

Color& Color::operator-=(const Color& rhs)
{
	r -= rhs.r;
	g -= rhs.g;
	b -= rhs.b;
	return *this;
}

Color& Color::operator*=(const Color& rhs)
{
	r *= rhs.r;
	g *= rhs.g;
	b *= rhs.b;
	return *this;
}

Color& Color::operator*=(float f)
{
	r *= f;
	g *= f;
	b *= f;
	return *this;
}

Color& Color::operator/=(const Color& rhs)
{
	r /= rhs.r;
	g /= rhs.g;
	b /= rhs.b;
	return *this;
}

Color& Color::operator/=(float f)
{
	r /= f;
	g /= f;
	b /= f;
	return *this;
}

void Color::Write(std::ostream& os)
{
	// Translate the [0,1] component values to the byte range [0,255].
	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	// Write out the pixel color components.
	os << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}