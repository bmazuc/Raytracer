#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

/**
 * Represents a numerical interval bounded by a minimum 
 * and a maximum value.
 */
class Interval
{
public:
	Interval();
	Interval(float inMin, float inMax);

	void SetMin(float inMin) { min = inMin; }
	void SetMax(float inMax) { max = inMax; }

	float Min() const { return min; }
	float Max() const { return max; }

	/**
	 * Returns the length of the interval.
	 * @return Difference between the maximum and minimum bounds.
	 */
	float Length() const;
	/**
	 * Checks whether a value belongs to the interval,
	 * including its boundaries.
	 *
	 * @param x Value to test.
	 * @return True if min <= x <= max.
	 */
	bool Contains(float x) const;
	/**
	 * Checks whether a value belongs strictly inside the interval.
	 * Excludes both boundary values.
	 *
	 * @param x Value to test.
	 * @return True if min < x < max.
	 */
	bool Surrounds(float x) const;
	/**
	 * Restricts a value to the interval boundaries.
	 *
	 * @param x Value to clamp.
	 * @return The clamped value.
	 */
	float Clamp(float x) const;

private:
	float min;
	float max;
};

#endif // RAYTRACER_INTERVAL_H