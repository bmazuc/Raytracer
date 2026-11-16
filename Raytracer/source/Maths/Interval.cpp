#include "Maths/Interval.h"
#include "Maths/MathsUtils.h"

Interval::Interval()
	: min(+MathsUtils::infinity), max(-MathsUtils::infinity)
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

float Interval::Clamp(float x) const
{
	if (x < min)
	{
		return min;
	}
	else if (x > max)
	{ 
		return max;
	}
	else
	{
		return x;
	}
}