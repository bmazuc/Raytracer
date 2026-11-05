#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

class Interval
{
public:
	Interval();
	Interval(float inMin, float inMax);

	void SetMin(float inMin) { min = inMin; }
	void SetMax(float inMax) { max = inMax; }

	float Min() const { return min; }
	float Max() const { return max; }

	float Size() const;
	bool Contains(float x) const;
	bool Surrounds(float x) const;
	float Clamp(float x) const;

private:
	float min;
	float max;
};

#endif // RAYTRACER_INTERVAL_H