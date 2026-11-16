#ifndef RAYTRACER_NUMERIC_UTILS_H
#define RAYTRACER_NUMERIC_UTILS_H

#include <limits>
#include <stdexcept>

/**
 * Provides utility functions for safe numeric conversions.
 */
namespace NumericUtils
{
    int ToInt(size_t value);
}

#endif // RAYTRACER_NUMERIC_UTILS_H