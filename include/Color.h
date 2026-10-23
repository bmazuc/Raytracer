#ifndef __COLOR_H_INCLUDED__
#define __COLOR_H_INCLUDED__

#include <iostream>

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
	Color operator/(const Color& rhs);
	Color operator/(float f) const;

	Color& operator+=(const Color& rhs);
	Color& operator-=(const Color& rhs);
	Color& operator*=(const Color& rhs);
	Color& operator*=(float f);
	Color& operator/=(const Color& rhs);
	Color& operator/=(float f);

	void Write(std::ostream& os);
};

inline Color operator*(float f, const Color& rhs)
{
	return rhs * f;
}

inline Color operator/(float f, const Color& rhs)
{
	return rhs / f;
}

#endif