#ifndef RAYTRACER_MATHS_H
#define RAYTRACER_MATHS_H

#include <limits>
#include <random>
#include "Interval.h"

namespace MathsUtils
{
    // Constants

    const float infinity = std::numeric_limits<float>::infinity();
    const float pi = 3.1415926535897932385f;

    // Utility Functions

    /**
     * Converts an angle from degrees to radians.
     *
     * @param degrees Angle expressed in degrees.
     * @return Equivalent angle expressed in radians.
     */
    inline float DegreesToRadians(float degrees)
    {
        return degrees * pi / 180.f;
    }

    /**
     * Generates a thread-local random floating-point value
     * in the range [0, 1).
     *
     * Each thread maintains its own random number generator
     * to avoid sharing mutable generator state.
     *
     * @return Random floating-point value.
     */
    inline float Random()
    {
        static std::atomic<std::mt19937::result_type> nextSeed{ 42 };

        static thread_local std::mt19937 generator
        {
            nextSeed.fetch_add(1, std::memory_order_relaxed) 
        };

        static thread_local std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

        return distribution(generator);
    }

    /**
     *  Generates a random floating-point value in the specified range.
     *
     * @param min Inclusive lower bound.
     * @param max Exclusive upper bound.
     * @return Random value in [min, max).
     */
    inline float Random(float min, float max)
    {
        return min + (max - min) * Random();
    }

    /**
     * Generates a random floating-point value within an interval.
     *
     * @param interval Interval defining the random value boundaries.
     * @return Random value within the interval.
     */
    inline float Random(Interval interval)
    {
        return Random(interval.Min(), interval.Max());
    }
}

#endif // RAYTRACER_MATHS_H