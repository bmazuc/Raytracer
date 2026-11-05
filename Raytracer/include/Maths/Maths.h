#ifndef RAYTRACER_MATHS_H
#define RAYTRACER_MATHS_H

#include <limits>
#include <random>
#include "Interval.h"

namespace maths
{
    // Constants

    const float infinity = std::numeric_limits<float>::infinity();
    const float pi = 3.1415926535897932385f;

    // Utility Functions

    inline float DegreesToRadians(float degrees)
    {
        return degrees * pi / 180.f;
    }

    // Returns a random real in [0,1).
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

    // Returns a random float in [min,max).
    inline float Random(float min, float max)
    {
        return min + (max - min) * Random();
    }

    // Returns a random float in [min,max).
    inline float Random(Interval interval)
    {
        return Random(interval.Min(), interval.Max());
    }
}

#endif // RAYTRACER_MATHS_H