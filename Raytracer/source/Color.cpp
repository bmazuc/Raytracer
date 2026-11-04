#include "Color.h"
#include "Maths/Maths.h"

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
	return Color(r / rhs.r, g / rhs.g, b / rhs.b);
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

Color Color::Lerp(const Color& colorA, const Color& colorB, float t)
{
	return (1.0f - t) * colorA + t * colorB;
}

Color Color::Random()
{
	return Color(maths::Random(), maths::Random(), maths::Random());
}

Color Color::Random(float min, float max)
{
	return Color(maths::Random(min, max),
		maths::Random(min, max),
		maths::Random(min, max));
}

Color Color::LinearToGamma(const Color& color)
{
	return Color(
		(color.r > 0) ? std::sqrt(color.r) : 0,
		(color.g > 0) ? std::sqrt(color.g) : 0,
		(color.b > 0) ? std::sqrt(color.b) : 0
	);
}