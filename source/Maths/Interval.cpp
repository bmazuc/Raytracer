#include "Maths/Interval.h"
#include "Maths/Maths.h"

Interval::Interval()
	: min(+maths::infinity), max(-maths::infinity)
{
}

Interval::Interval(float inMin, float inMax) 
	: min(inMin), max(inMax)
{
}

float Interval::Size() const
{
	return max - min;
}

bool Interval::Contains(float x) const
{
	return min <= x && x <= max;
}

bool Interval::Surrounds(float x) const
{
	return min < x && x < max;
}