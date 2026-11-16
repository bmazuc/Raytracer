#ifndef RAYTRACER_NUMERIC_UTILS_H
#define RAYTRACER_NUMERIC_UTILS_H

#include <limits>
#include <stdexcept>

/**
 * Provides utility functions for safe numeric conversions.
 */
namespace NumericUtils
{
    /**
     * Converts an unsigned integer to an integer with range validation.
     * Throws an exception if the value cannot be represented by an int.
     *
     * @param value Value to convert.
     * @return Converted integer.
     * @throws std::overflow_error If the value exceeds the maximum
     * representable int value.
     */
    int ToInt(size_t value);
}

#endif // RAYTRACER_NUMERIC_UTILS_H